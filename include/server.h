/*
    Created by Maor Gershman, 14.9.2019
    ---
    These classes will represent the server's address and port.
*/

#pragma once

#include <sstream>

namespace SatelliteSoftware {
    template<int Byte0, int Byte1, int Byte2, int Byte3>
    struct Address {
        static_assert(
            Byte0 >= 0 && Byte0 <= 0xFF &&
            Byte1 >= 0 && Byte1 <= 0xFF &&
            Byte2 >= 0 && Byte2 <= 0xFF &&
            Byte3 >= 0 && Byte3 <= 0xFF,
            "Bad address!"
        );

        inline constexpr std::string to_string() const {
            std::stringstream ss;
            ss << Byte0 << "." << Byte1 << "." << Byte2 << "." << Byte3;
            return ss.str();
        }
    };

    template<typename ServerAddress, int ServerPort>
    struct Server {
        ServerAddress address;
        const int port = ServerPort;

        static_assert(ServerPort > 0 && ServerPort < 0xFFFF, "Bad port!");
    };
}