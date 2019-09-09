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

namespace SatelliteSoftware {
    class IMU {
    private:
        std::unique_ptr<MPU9250_Master_I2C> mpu;
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

        std::array<float, 3> read_magnetometer() {
            float mx, my, mz;
            mpu->readMagnetometer(mx, my, mz);
            return {mx, my, mz};
        }
        
        std::array<float, 3> read_gyrometer() {
            float gx, gy, gz;
            mpu->readGyrometer(gx, gy, gz);
            return {gx, gy, gz};
        }
        
        std::array<float, 3> read_accelerometer() {
            float gx, gy, gz;
            mpu->readAccelerometer(gx, gy, gz);
            return {gx, gy, gz};}
    };
}
#endif // RASPBERRY_PI