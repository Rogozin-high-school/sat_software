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
        };

        const Type& type;

        inline PacketIn(int socketHandle) :
            socketHandle(socketHandle), type(propType) 
        {}

        template<int BufferSize>
        inline const std::array<char, BufferSize> receive_packet() {
            static_assert(BufferSize > 0 && BufferSize <= 1024);

            std::array<char, BufferSize> buffer;
            if (read(socketHandle, buffer.begin(), BufferSize) <= 0)
                throw std::exception();

            switch (static_cast<PacketInType>(buffer[0])) {
            case PacketInType::KEEPALIVE:
                propType = PacketInType::KEEPALIVE;
                break;
            case PacketInType::REQUIRE_MGM_VALUES:
                propType = PacketInType::REQUIRE_MGM_VALUES;
                break;
            default:
                propType = PacketInType::UNKNOWN;
                break;
            }

            return buffer;
        }
    private:
        const int socketHandle;
        Type propType;
    };
}