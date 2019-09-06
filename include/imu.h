/*
    Created by Maor Gershman, 6.9.2019
    ---
    This class will manage the satellite's IMU.
*/

#pragma once

#ifdef RASPBERRY_PI
#include "../lib/MPU/MPU9250_Master_I2C.h"
#include "logger.h"
#include <wiringPi.h>
#include <memory>
#include <array>

namespace SatelliteSoftware {
    class IMU {
    private:
        std::unique_ptr<MPU9250_Master_I2C> mpu;
        std::array<std::array<float, 3>, 3> values;
    public:
        IMU() {
            Logger::debug("Setting up WiringPi...", Logger::Prefix::IMU);
            wiringPiSetup();

            Logger::debug("Setting up MPU...", Logger::Prefix::IMU);
            mpu = std::make_unique<MPU9250_Master_I2C>
                (MPU9250_Master_I2C::AFS_2G,
                MPU9250_Master_I2C::GFS_250DPS, 
                MPU9250_Master_I2C::MFS_16BITS, 
                MPU9250_Master_I2C::M_8Hz);
            
            Logger::debug("Starting MPU...", Logger::Prefix::IMU);
            switch (mpu->begin()) {
            case MPUIMU::ERROR_NONE:
                Logger::info("Ready!", Logger::Prefix::IMU);
                break;
            case MPUIMU::ERROR_IMU_ID:
                Logger::severe("Bad IMU device ID!", Logger::Prefix::IMU);
                break;
            case MPUIMU::ERROR_MAG_ID:
                Logger::severe("Bad MGM device ID!", Logger::Prefix::IMU);
                break;
            case MPUIMU::ERROR_SELFTEST:
                Logger::severe("Failed self test!", Logger::Prefix::IMU);
                break;
            }
        }

        void calibrate_magnetometer() {
            mpu->calibrateMagnetometer();
        }

        void read_Magnetometer() {
            mpu->readMagnetometer(values[0][0], values[0][1], values[0][2]);
        }
        
        void read_gyrometer() {
            mpu->readGyrometer(values[1][0], values[1][1], values[1][2]);
        }
        
        void read_accelerometer() {
            mpu->readAccelerometer(values[2][0], values[2][1], values[2][2]);
        }
    };
}
#endif // RASPBERRY_PI