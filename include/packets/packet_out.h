/*
    Created by Maor Gershman, 13.9.2019
    ---
    This class will represent data sent to the ground station.
*/

#pragma once

#include "../main.h"
#include <unistd.h>

namespace SatelliteSoftware::Packets {
    constexpr Byte senderID = 1; // Satellite ID = 1

    template<int size>
    class PacketOut {
    public:
        inline PacketOut(const Socket sock) : sock(sock) {
            static_assert(size > 0 && size <= maxPacketSize);
            buffer[0] = senderID;
        }

        inline void send_packet() const {
            send(sock, buffer, size, 0);
        }
    protected:
        Byte buffer[size];
    private:
        const Socket sock;
    };
}