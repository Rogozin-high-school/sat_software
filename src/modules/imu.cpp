#include <modules/imu.hpp>
#include <logger.hpp>

#ifdef RASPBERRY_PI // Real IMU

namespace Modules {
    IMU::IMU() : 
        mpu(MPU9250_Master_I2C::AFS_2G,
            MPU9250_Master_I2C::GFS_250DPS,
            MPU9250_Master_I2C::MFS_16BITS,
            MPU9250_Master_I2C::M_8Hz
        ) 
    {}

    void IMU::initialize() {
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

    void IMU::calibrate_magnetometer() {
        // Maybe will be used in the future.
        mpu.calibrateMagnetometer();
    }

    std::array<float, 3> IMU::read_magnetometer() {
        float mx, my, mz;
        mpu.readMagnetometer(mx, my, mz);

        Logger::debug("Read MGM values: (" + 
            std::to_string(mx) + ", " + 
            std::to_string(my) + ", " + 
            std::to_string(mz) + ")",
            LogPrefix::IMU);
        
        return { mx, my, mz };
    }

    std::array<float, 3> IMU::read_gyrometer() {
        float gx, gy, gz;
        mpu.readGyrometer(gx, gy, gz);
        return { gx, gy, gz };
    }

    std::array<float, 3> IMU::read_accelerometer() {
        float gx, gy, gz;
        mpu.readAccelerometer(gx, gy, gz);
        return { gx, gy, gz };
    }
}

#else // Fake IMU

#include <random>

namespace Modules {
    void IMU::initialize() {
        // Kept to be compatible with the original IMU!
        Logger::info("Ready!", LogPrefix::IMU);
    }

    void IMU::calibrate_magnetometer() {
        // Maybe will be used in the future.
        // Meanwhile kept to be compatible with the original IMU.
    }

    std::array<float, 3> IMU::read_magnetometer() {
        // Use random values.
        // Good values for a standing still satellite in the lab will be:
        // X:  5 µT ± 2µT
        // Y:  25µT ± 2µT
        // Z: -28µT ± 2µT
        std::mt19937 generator(std::random_device{}());
        std::uniform_real_distribution<> distribution(-2.0f, 2.0f); // ± 2
        float mx =   5.0f + distribution(generator);
        float my =  25.0f + distribution(generator);
        float mz = -28.0f + distribution(generator);

        Logger::debug("Read MGM values: (" + 
            std::to_string(mx) + ", " + 
            std::to_string(my) + ", " + 
            std::to_string(mz) + ")",
            LogPrefix::IMU);
        
        return { mx, my, mz };
    }

    std::array<float, 3> IMU::read_gyrometer() {
        // Will be used later.
        return { 0.0f, 0.0f, 0.0f };
    }

    std::array<float, 3> IMU::read_accelerometer() {
        // Will be used later.
        return { 0.0f, 0.0f, 0.0f };
    }
}

#endif // RASPBERRY_PI