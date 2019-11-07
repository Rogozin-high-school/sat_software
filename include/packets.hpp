#pragma once

#include <modules/magnetorquer/magnetorquer.hpp>
#include <client_base.hpp>
#include <variant>
#include <algorithm>
#include <thread>
#include <chrono>
#include <unistd.h>

namespace Packets {
    enum class PacketId : Byte {
        KEEPALIVE       = 0x00,
        MGM             = 0x01,
        MAGNETORQUER    = 0x02
    };

    // Valid in packets

    class KeepAlivePacket { // Singleton
    public:
        static const KeepAlivePacket instance;
    private:
        KeepAlivePacket() {}
    };

    class RequireMGMValuesPacket { // Singleton
    public:
        static const RequireMGMValuesPacket instance;
    private:
        RequireMGMValuesPacket() {}
    };

    class UseMagnetorquerPacket {
        static constexpr auto torqueEpoch = std::chrono::seconds(1);
    public:
        static constexpr uint8_t size = 3;

        const std::unordered_map<Axis, Modules::HBridge::Direction> torqueDirections;

        UseMagnetorquerPacket(const std::array<Byte, size> bytes);

        void start_torque(Modules::Magnetorquer& magnetorquer);
    };

    using ValidInPacket = std::variant<
        KeepAlivePacket,
        RequireMGMValuesPacket,
        UseMagnetorquerPacket
    >;

    // Out packets

    class KeepAliveResponsePacket { // Singleton
    public:
        static constexpr PacketId id = PacketId::KEEPALIVE;

        static constexpr uint8_t size = 0;

        static const KeepAliveResponsePacket instance;
    private:
        KeepAliveResponsePacket() {}
    };

    class RequireMGMValuesResponsePacket {
    public:
        static constexpr PacketId id = PacketId::MGM;

        static constexpr uint8_t size = 3 * sizeof(float);

        std::array<Byte, size> buffer;

        RequireMGMValuesResponsePacket(std::unordered_map<Axis, float> mgmValues);
    };
    
    class UseMagnetorquerResponsePacket { // Singleton
    public:
        static constexpr PacketId id = PacketId::MAGNETORQUER;

        static constexpr uint8_t size = 0;

        static const UseMagnetorquerResponsePacket instance;
    private:
        UseMagnetorquerResponsePacket() {}
    };

    using OutPacket = std::variant<
        KeepAlivePacket,
        RequireMGMValuesResponsePacket,
        UseMagnetorquerResponsePacket
    >;

    // Unknown packet

    class UnknownPacket { // Singleton
    public:
        static const UnknownPacket instance;
    private:
        UnknownPacket() {}
    };

    // Error packet

    class ErrorPacket { // Singleton
    public:
        static const ErrorPacket instance;
    private:
        ErrorPacket() {}
    };

    using ReceivablePacket = std::variant<ValidInPacket, UnknownPacket, ErrorPacket>;

    static inline ReceivablePacket receive_packet(Socket socketFD) {
        std::array<Byte, maxPacketSize> buffer;
        if (read(socketFD, buffer.begin(), buffer.size()) > 0) {
            PacketId id = PacketId(buffer.front());

            // Check the packet's ID
            switch (id) {
                case PacketId::KEEPALIVE: 
                    return ValidInPacket { KeepAlivePacket::instance };
                case PacketId::MGM:
                    return ValidInPacket { RequireMGMValuesPacket::instance };
                case PacketId::MAGNETORQUER: {
                    std::array<Byte, UseMagnetorquerPacket::size> cutBuffer;
                    std::copy(buffer.begin() + 1, buffer.end(), cutBuffer.begin());

                    return ValidInPacket { UseMagnetorquerPacket(cutBuffer) };
                }
            }
            return UnknownPacket::instance;
        }
        return ErrorPacket::instance;
    }

    template<class T>
    static inline bool send_packet(T outPacket, Socket socketFD) {
        std::array<Byte, 1 + T::size> buffer;
        
        if constexpr(T::size > 0) {
            buffer[0] = Byte(T::id);
            std::copy(buffer.begin() + 1, buffer.end(), outPacket.buffer.begin());
        }

        return send(socketFD, buffer.begin(), buffer.size(), 0) > 0;
    }

    static inline bool is_unknown_packet(const ReceivablePacket& packet) {
        return packet.index() == 1;
    }

    static inline bool is_error_packet(const ReceivablePacket& packet) {
        return packet.index() == 2;
    }
}