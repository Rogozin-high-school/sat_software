/*
    Created by Maor Gershman, 6.9.2019
    ---
    This class will manage the satellite's IMU.
*/

#pragma once

#include "main.h"

#ifdef RASPBERRY_PI
#include "../lib/MPU/MPU9250_Master_I2C.h"

namespace SatelliteSoftware {
    class IMU {
    private:
        std::unique_ptr<MPU9250_Master_I2C> mpu;
    public:
        IMU();

        void calibrate_magnetometer();

        std::array<float, 3> read_magnetometer();
        
        std::array<float, 3> read_gyrometer();
        
        std::array<float, 3> read_accelerometer();
    };
}
#endif // RASPBERRY_PI