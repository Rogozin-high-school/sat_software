/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will manage the satellite's RealIMU.
*/

#include "../include/imu.h"

#ifdef RASPBERRY_PI

#include "../include/logger.h"
#include <memory>

namespace SatelliteSoftware {
    RealIMU::RealIMU() : 
        mpu(MPU9250_Master_I2C::AFS_2G,
            MPU9250_Master_I2C::GFS_250DPS,
            MPU9250_Master_I2C::MFS_16BITS,
            MPU9250_Master_I2C::M_8Hz
        ) 
    {}

    void RealIMU::initialize() {
        Logger::debug("Initializing MPU...", LogPrefix::IMU);
        switch (mpu.begin()) {
        case MPUIMU::ERROR_IMU_ID:
            throw std::runtime_error("Bad IMU device ID!");
        case MPUIMU::ERROR_MAG_ID:
            throw std::runtime_error("Bad MGM device ID!");
        case MPUIMU::ERROR_SELFTEST:
            throw std::runtime_error("Failed self test!");
        }            
        Logger::info("Ready!", LogPrefix::IMU);
    }

    void RealIMU::calibrate_magnetometer() {
        // Maybe will be used in the future.
        mpu.calibrateMagnetometer();
    }

    std::array<float, 3> RealIMU::read_magnetometer() {
        float mx, my, mz;
        mpu.readMagnetometer(mx, my, mz);

        Logger::debug("Read MGM values: (" + 
            std::to_string(mx) + ", " + 
            std::to_string(my) + ", " + 
            std::to_string(mz) + ")",
            LogPrefix::IMU);
        
        return {mx, my, mz};
    }
    
    std::array<float, 3> RealIMU::read_gyrometer() {
        float gx, gy, gz;
        mpu.readGyrometer(gx, gy, gz);
        return {gx, gy, gz};
    }
    
    std::array<float, 3> RealIMU::read_accelerometer() {
        float gx, gy, gz;
        mpu.readAccelerometer(gx, gy, gz);
        return {gx, gy, gz};
    }
}
#endif // RASPBERRY_PI