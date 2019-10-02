/*
    Created by Maor Gershman, 13.9.2019
    ---
    This class will represent data sent from the ground station.
*/

#pragma once

#include "../main.h"
#include <unistd.h>

namespace SatelliteSoftware::Packets {
    class PacketIn {
    public:
        enum class Type {
            UNKNOWN            = -1,
            KEEPALIVE          = 0,
            REQUIRE_MGM_VALUES = 1,
            USE_TORQ           = 2,
        };

        const PacketIn::Type& type = propType;

        inline PacketIn(const Socket sock) : sock(sock)
        {}

        template<int size>
        inline const std::optional<std::array<Byte, size>> receive_packet() {
            static_assert(size > 0 && size <= maxPacketSize);
            std::array<Byte, size> buffer;
            if (read(sock, buffer.begin(), size) <= 0)
                return std::nullopt;
            switch (static_cast<PacketIn::Type>(buffer[0])) {
            case PacketIn::Type::KEEPALIVE:
                propType = PacketIn::Type::KEEPALIVE;
                break;
            case PacketIn::Type::REQUIRE_MGM_VALUES:
                propType = PacketIn::Type::REQUIRE_MGM_VALUES;
                break;
            case PacketIn::Type::USE_TORQ:
                propType = PacketIn::Type::USE_TORQ;
                break;
            }
            }
            return buffer;
        }
    private:
        const Socket sock;
        PacketIn::Type propType = PacketIn::Type::UNKNOWN;
    };
}