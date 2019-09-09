/*
    Created by Maor Gershman, 8.9.2019
    ---
    This class will fake the IMU, for testing on the PC.
*/

#pragma once

#include "main.h"

#ifndef RASPBERRY_PI
namespace SatelliteSoftware {
    class FakeIMU {
    public:
        FakeIMU();

        void calibrate_magnetometer();

        std::array<float, 3> read_magnetometer();
        
        std::array<float, 3> read_gyrometer();
        
        std::array<float, 3> read_accelerometer();
    };
}
#endif // RASPBERRY_PI