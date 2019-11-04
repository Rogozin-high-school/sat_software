/*
    Created by Maor Gershman, 13.9.2019
    ---
    This class will represent data sent to the ground station.
*/

#pragma once

#include <client_base.hpp>
#include <unistd.h>

namespace Packets {
    constexpr Byte senderID = 1; // Satellite ID = 1

    template<int size>
    class PacketOut {
    public:
        PacketOut(const Socket sock) : sock(sock) {
            static_assert(size > 0 && size <= maxPacketSize);
            buffer[0] = senderID;
        }

        void send_packet() const {
            send(sock, buffer, size, 0);
        }
    protected:
        Byte buffer[size];
    private:
        const Socket sock;
    };
}