/*
    Created by Maor Gershman, 13.9.2019
    ---
    This class will represent data sent from the ground station.
*/

#pragma once

#include <client_base.hpp>
#include <unistd.h>
#include <optional>

namespace Packets {
    class PacketIn {
    public:
        enum class Type : Byte {
            UNKNOWN            = 0xff,
            
            KEEPALIVE          = 0x00,
            REQUIRE_MGM_VALUES = 0x01,
            USE_TORQUE         = 0x02
        };

        const PacketIn::Type& type = _type;

        PacketIn(const Socket socketFD) : socketFD(socketFD)
        {}

        template<int size>
        const std::optional<std::array<Byte, size>> receive_packet() {
            static_assert(size > 0 && size <= maxPacketSize);
            
            std::array<Byte, size> buffer;
            if (read(socketFD, buffer.begin(), size) <= 0) {
                return std::nullopt;
            }

            Byte packetTypeId = buffer.front();
            auto packetType = static_cast<PacketIn::Type>(packetTypeId);

            switch (packetTypeId) {
            case PacketIn::Type::KEEPALIVE:
                _type = PacketIn::Type::KEEPALIVE;
                break;
            case PacketIn::Type::REQUIRE_MGM_VALUES:
                _type = PacketIn::Type::REQUIRE_MGM_VALUES;
                break;
            case PacketIn::Type::USE_TORQUE:
                _type = PacketIn::Type::USE_TORQUE;
                break;
            }
            
            return buffer;
        }
    private:
        const Socket socketFD;
        PacketIn::Type _type = PacketIn::Type::UNKNOWN;
    };
}
