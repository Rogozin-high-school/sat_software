/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will manage the satellite's RealIMU.
*/

#include "../include/imu.h"

#ifdef RASPBERRY_PI

#include "../include/logger.h"
#include <wiringPi.h>
#include <memory>

namespace SatelliteSoftware {
    RealIMU::RealIMU() : propAllOk(true), allOk(propAllOk) {
        Logger::debug("Setting up WiringPi...", LogPrefix::REALIMU);
        wiringPiSetup();

        Logger::debug("Setting up MPU...", LogPrefix::REALIMU);
        mpu = std::make_unique<MPU9250_Master_I2C>
            (MPU9250_Master_I2C::AFS_2G,
            MPU9250_Master_I2C::GFS_250DPS, 
            MPU9250_Master_I2C::MFS_16BITS, 
            MPU9250_Master_I2C::M_8Hz);
        
        Logger::debug("Starting MPU...", LogPrefix::REALIMU);
        switch (mpu->begin()) {
        case MPUIMU::ERROR_NONE:
            Logger::info("Ready!", LogPrefix::REALIMU);
            break;
        case MPUIMU::ERROR_IMU_ID:
            Logger::error("Bad IMU device ID!", LogPrefix::REALIMU);
            propAllOk = false;
            break;
        case MPUIMU::ERROR_MAG_ID:
            Logger::error("Bad MGM device ID!", LogPrefix::REALIMU);
            propAllOk = false;
            break;
        case MPUIMU::ERROR_SELFTEST:
            Logger::error("Failed self test!", LogPrefix::REALIMU);
            propAllOk = false;
            break;
        }
    }

    void RealIMU::calibrate_magnetometer() {
        mpu->calibrateMagnetometer();
    }

    std::array<float, 3> RealIMU::read_magnetometer() {
        float mx, my, mz;
        mpu->readMagnetometer(mx, my, mz);
        return {mx, my, mz};
    }
    
    std::array<float, 3> RealIMU::read_gyrometer() {
        float gx, gy, gz;
        mpu->readGyrometer(gx, gy, gz);
        return {gx, gy, gz};
    }
    
    std::array<float, 3> RealIMU::read_accelerometer() {
        float gx, gy, gz;
        mpu->readAccelerometer(gx, gy, gz);
        return {gx, gy, gz};
    }
}
#endif // RASPBERRY_PI