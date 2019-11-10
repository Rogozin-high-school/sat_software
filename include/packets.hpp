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

    class KeepAlivePacket {};

    class RequireMGMValuesPacket {};

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

    class KeepAliveResponsePacket {
    public:
        static constexpr PacketId id = PacketId::KEEPALIVE;

        static constexpr uint8_t size = 0;
    };

    class RequireMGMValuesResponsePacket {
    public:
        static constexpr PacketId id = PacketId::MGM;

        static constexpr uint8_t size = 3 * sizeof(float);

        std::array<Byte, size> buffer;

        RequireMGMValuesResponsePacket(std::unordered_map<Axis, float> mgmValues);
    };
    
    class UseMagnetorquerResponsePacket {
    public:
        static constexpr PacketId id = PacketId::MAGNETORQUER;

        static constexpr uint8_t size = 0;
    };

    using OutPacket = std::variant<
        KeepAlivePacket,
        RequireMGMValuesResponsePacket,
        UseMagnetorquerResponsePacket
    >;

    class UnknownPacket {};

    class ErrorPacket {};

    using ReceivablePacket = std::variant<ValidInPacket, UnknownPacket, ErrorPacket>;

    ReceivablePacket receive_packet(Socket socketFD);

    bool is_unknown_packet(const ReceivablePacket& packet);

    bool is_error_packet(const ReceivablePacket& packet);
}