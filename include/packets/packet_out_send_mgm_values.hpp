/*
    Created by Maor Gershman, 13.9.2019
    ---
    This packet will contain data about the MGM values.
*/

#pragma once

#include <packets/packet_out.hpp>
#include <modules/imu.hpp>
#include <cstring>

namespace Packets {
    class PacketOutSendMGMValues : public PacketOut<1 + 12> {
    public:
        PacketOutSendMGMValues(const Socket socketFD, Modules::IMU& imu) : PacketOut(socketFD) {
            std::array values = imu.read_magnetometer();
            // Copy the values to the buffer
            for (int i = 0; i < 3; i++) {
                memcpy(buffer + i * sizeof(float) + 1, &values[i], sizeof(float));
            }
        }
    };
}