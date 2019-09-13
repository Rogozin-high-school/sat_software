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

        const Type& type = propType;

        inline PacketIn(int socketHandle) : socketHandle(socketHandle)
        {}

        template<int BufferSize>
        inline const std::array<char, BufferSize> receive_packet() {
            static_assert(BufferSize > 0 && BufferSize <= 1024);

            std::array<char, BufferSize> buffer;
            if (read(socketHandle, buffer.begin(), BufferSize) <= 0)
                throw std::exception();

            switch (static_cast<Type>(buffer[0])) {
            case Type::KEEPALIVE:
                propType = Type::KEEPALIVE;
                break;
            case Type::REQUIRE_MGM_VALUES:
                propType = Type::REQUIRE_MGM_VALUES;
                break;
            }

            return buffer;
        }
    private:
        const int socketHandle;
        Type propType = Type::UNKNOWN;
    };
}