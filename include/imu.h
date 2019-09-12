/*
    Created by Maor Gershman, 6.9.2019
    ---
    This class will manage the satellite's IMU.
*/

#pragma once

#include "main.h"

#ifdef RASPBERRY_PI
#include "../lib/MPU/MPU9250_Master_I2C.h"
#endif

namespace SatelliteSoftware {
    #ifdef RASPBERRY_PI
    class RealIMU {
    private:
        std::unique_ptr<MPU9250_Master_I2C> mpu;

        bool propAllOk;
    public:
        bool& allOk;

        RealIMU();

        void calibrate_magnetometer();

        std::array<float, 3> read_magnetometer();
        
        std::array<float, 3> read_gyrometer();
        
        std::array<float, 3> read_accelerometer();
    };
    using IMU = RealIMU;
    #else
    class FakeIMU {
    private:
        bool propAllOk;
    public:
        bool& allOk;

        FakeIMU();

        void calibrate_magnetometer();

        std::array<float, 3> read_magnetometer();
        
        std::array<float, 3> read_gyrometer();
        
        std::array<float, 3> read_accelerometer();
    };
    using IMU = FakeIMU;
    #endif // RASPBERRY_PI
}