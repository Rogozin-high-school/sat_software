#include <packets.hpp>
#include <logger.hpp>

namespace Packets {
    const KeepAlivePacket           KeepAlivePacket::instance;
    const RequireMGMValuesPacket    RequireMGMValuesPacket::instance;
    const UnknownPacket             UnknownPacket::instance;
    const ErrorPacket               ErrorPacket::instance;

    // UseMagnetorquerPacket

    template<size_t size>
    inline const auto directionsBufferToMap(const std::array<Byte, size>& bytes) {
        using namespace Modules::SubModules;

        std::unordered_map<Axis, HBridge::Direction> map;
        map[Axis::X] = static_cast<HBridge::Direction>(bytes[0]);
        map[Axis::Y] = static_cast<HBridge::Direction>(bytes[1]);
        map[Axis::Z] = static_cast<HBridge::Direction>(bytes[2]);

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