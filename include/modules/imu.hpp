/*
    Created by Maor Gershman, 6.9.2019
    ---
    This class will manage the satellite's IMU.
*/

#pragma once

#include <array>

#ifdef RASPBERRY_PI // Real IMU

#include <MPU/MPU9250_Master_I2C.h>

namespace Modules {
    class IMU {
    public:
        IMU();

        void initialize();

        void calibrate_magnetometer();

        std::array<float, 3> read_magnetometer();
        
        std::array<float, 3> read_gyrometer();
        
        std::array<float, 3> read_accelerometer();
    private:
        MPU9250_Master_I2C mpu;
    };
}

#else // Fake IMU

namespace Modules { 
    class IMU {
    public:
        void initialize();

        void calibrate_magnetometer();

        std::array<float, 3> read_magnetometer();
        
        std::array<float, 3> read_gyrometer();
        
        std::array<float, 3> read_accelerometer();
    };
}

#endif // RASPBERRY_PI