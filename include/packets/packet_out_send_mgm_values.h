/*
    Created by Maor Gershman, 13.9.2019
    ---
    This packet will contain data about the MGM values.
*/

#pragma once

#include "packet_out.h"
#include "../imu.h"

namespace SatelliteSoftware::Packets {
    class PacketOutSendMGMValues : public PacketOut<13> {
    public:
        inline PacketOutSendMGMValues(int socketHandle, IMU& imu) : PacketOut(socketHandle) {
            std::array values = imu.read_magnetometer();
            // Copy the values to the buffer
            for (int i = 0; i < 3; i++)
                memcpy(buffer + i * sizeof(float) + 1, &values[i], sizeof(float));
        }
    };
}