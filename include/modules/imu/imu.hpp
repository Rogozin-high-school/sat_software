/*
    Created by Maor Gershman, 6.9.2019
    ---
    This class will manage the satellite's IMU.
*/

#pragma once

#include <modules/module_base.hpp>

#ifdef RASPBERRY_PI
#include <MPU9250_Master_I2C.h>
#endif // RASPBERRY_PI

namespace Modules {
    class IMU {
    public:
        void initialize();
        void calibrate_magnetometer();
        std::unordered_map<Axis, float> read_magnetometer();
#ifdef RASPBERRY_PI
    private:
        MPU9250_Master_I2C mpu {
            MPU9250_Master_I2C::AFS_2G,
            MPU9250_Master_I2C::GFS_250DPS,
            MPU9250_Master_I2C::MFS_16BITS,
            MPU9250_Master_I2C::M_8Hz
        };
#endif // RASPBERRY_PI
    };
}