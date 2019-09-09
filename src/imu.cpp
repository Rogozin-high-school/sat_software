/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will manage the satellite's IMU.
*/

#include "../include/imu.h"

#ifdef RASPBERRY_PI

#include "../include/logger.h"
#include <wiringPi.h>
#include <memory>

namespace SatelliteSoftware {
    IMU::IMU() {
        Logger::debug("Setting up WiringPi...", LogPrefix::IMU);
        wiringPiSetup();

        Logger::debug("Setting up MPU...", LogPrefix::IMU);
        mpu = std::make_unique<MPU9250_Master_I2C>
            (MPU9250_Master_I2C::AFS_2G,
            MPU9250_Master_I2C::GFS_250DPS, 
            MPU9250_Master_I2C::MFS_16BITS, 
            MPU9250_Master_I2C::M_8Hz);
        
        Logger::debug("Starting MPU...", LogPrefix::IMU);
        switch (mpu->begin()) {
        case MPUIMU::ERROR_NONE:
            Logger::info("Ready!", LogPrefix::IMU);
            break;
        case MPUIMU::ERROR_IMU_ID:
            Logger::severe("Bad IMU device ID!", LogPrefix::IMU);
            break;
        case MPUIMU::ERROR_MAG_ID:
            Logger::severe("Bad MGM device ID!", LogPrefix::IMU);
            break;
        case MPUIMU::ERROR_SELFTEST:
            Logger::severe("Failed self test!", LogPrefix::IMU);
            break;
        }
    }

    void IMU::calibrate_magnetometer() {
        mpu->calibrateMagnetometer();
    }

    std::array<float, 3> IMU::read_magnetometer() {
        float mx, my, mz;
        mpu->readMagnetometer(mx, my, mz);
        return {mx, my, mz};
    }
    
    std::array<float, 3> IMU::read_gyrometer() {
        float gx, gy, gz;
        mpu->readGyrometer(gx, gy, gz);
        return {gx, gy, gz};
    }
    
    std::array<float, 3> IMU::read_accelerometer() {
        float gx, gy, gz;
        mpu->readAccelerometer(gx, gy, gz);
        return {gx, gy, gz};
    }
}
#endif // RASPBERRY_PI