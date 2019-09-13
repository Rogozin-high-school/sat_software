/*
    Created by Maor Gershman, 13.9.2019
    ---
    This class will represent data sent to the ground station.
*/

#pragma once

#include "../main.h"
#include <unistd.h>

namespace SatelliteSoftware::Packets {
    constexpr int SenderID = 1; // Satellite ID = 1

    template<int BufferSize>
    class PacketOut {
    public:
        inline PacketOut(int socketHandle) : socketHandle(socketHandle) {
            static_assert(BufferSize > 0 && BufferSize <= 1024);
            buffer[0] = SenderID;
        }

        inline void send_packet() const {
            send(socketHandle, buffer, BufferSize, 0);
        }
    protected:
        char buffer[BufferSize];
    private:
        const int socketHandle;
    };
}