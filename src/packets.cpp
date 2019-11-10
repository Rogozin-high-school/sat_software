#include <packets.hpp>
#include <logger.hpp>

namespace Packets {
    ReceivablePacket receive_packet(Socket socketFD) {
        std::array<Byte, maxPacketSize> buffer;
        if (read(socketFD, buffer.begin(), buffer.size()) > 0) {
            PacketId id = PacketId(buffer.front());

            // Check the packet's ID
            switch (id) {
                case PacketId::KEEPALIVE: 
                    return ValidInPacket { KeepAlivePacket {} };
                case PacketId::MGM:
                    return ValidInPacket { RequireMGMValuesPacket {} };
                case PacketId::MAGNETORQUER: {
                    std::array<Byte, UseMagnetorquerPacket::size> cutBuffer;
                    std::copy(buffer.begin() + 1, buffer.end(), cutBuffer.begin());

                    return ValidInPacket { UseMagnetorquerPacket(cutBuffer) };
                }
            }
            return UnknownPacket {};
        }
        return ErrorPacket {};
    }

    bool is_unknown_packet(const ReceivablePacket& packet) {
        return packet.index() == 1;
    }

    bool is_error_packet(const ReceivablePacket& packet) {
        return packet.index() == 2;
    }

    // UseMagnetorquerPacket

    template<size_t size>
    inline const auto directionsBufferToMap(const std::array<Byte, size>& bytes) {
        std::unordered_map<Axis, Modules::HBridge::Direction> map;
        map[Axis::X] = Modules::HBridge::Direction(bytes[0]);
        map[Axis::Y] = Modules::HBridge::Direction(bytes[1]);
        map[Axis::Z] = Modules::HBridge::Direction(bytes[2]);
        return map;
    }

    UseMagnetorquerPacket::UseMagnetorquerPacket(const std::array<Byte, size> bytes)
        : torqueDirections(directionsBufferToMap(bytes))
    {}

    void UseMagnetorquerPacket::start_torque(Modules::Magnetorquer& magnetorquer) {
        Logger::debug<LogPrefix::MAGNETORQUER>("Starting torque!");
        for (auto& pair : torqueDirections) {
            magnetorquer.set_torque_direction(pair.first, pair.second);
        }
        Logger::debug<LogPrefix::MAGNETORQUER>("Sleeping for " + std::to_string(torqueEpoch.count()) + "!");
        std::this_thread::sleep_for(torqueEpoch);
        Logger::debug<LogPrefix::MAGNETORQUER>("Reset torque!");
        magnetorquer.reset_torque_directions();
    }

    // RequireMGMValuesResponsePacket

    RequireMGMValuesResponsePacket::RequireMGMValuesResponsePacket(std::unordered_map<Axis, float> mgmValues) {
        std::fill(buffer.begin() + sizeof(float) * 0, buffer.begin() + sizeof(float) * 1, mgmValues[Axis::X]);
        std::fill(buffer.begin() + sizeof(float) * 1, buffer.begin() + sizeof(float) * 2, mgmValues[Axis::Y]);
        std::fill(buffer.begin() + sizeof(float) * 2, buffer.begin() + sizeof(float) * 3, mgmValues[Axis::Z]);
    }
}