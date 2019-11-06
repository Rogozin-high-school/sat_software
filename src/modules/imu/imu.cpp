#include <modules/imu/imu.hpp>
#include <logger.hpp>
#include <random>

namespace Modules {
    void IMU::initialize() {
        Logger::verbose<LogPrefix::IMU>("Initializing MPU...");
#ifdef RASPBERRY_PI
        switch (mpu.begin()) {
        case MPUIMU::ERROR_IMU_ID:
            throw std::runtime_error("Bad IMU device ID!");
        case MPUIMU::ERROR_MAG_ID:
            throw std::runtime_error("Bad MGM device ID!");
        case MPUIMU::ERROR_SELFTEST:
            throw std::runtime_error("Failed self test!");
        }
#endif // RASPBERRY_PI
        Logger::debug<LogPrefix::IMU>("Ready!");
    }

    void IMU::calibrate_magnetometer() {
#ifdef RASPBERRY_PI
        mpu.calibrateMagnetometer(); // Maybe will be used in the future.
#endif // RASPBERRY_PI
    }

    std::unordered_map<Axis, float> IMU::read_magnetometer() {
        float mx = 0, my = 0, mz = 0;
#ifdef RASPBERRY_PI
        mpu.readMagnetometer(mx, my, mz);
#else // Fake values
        std::mt19937 generator(std::random_device {}());
        std::uniform_real_distribution<> distribution(-2, 2); // ± 2
        // Good values for a standing still satellite in the lab will be:
        mx =   5 + distribution(generator); // 5 µT ± 2µT
        my =  25 + distribution(generator); // 25µT ± 2µT
        mz = -28 + distribution(generator); // -28µT ± 2µT
#endif // RASPBERRY_PI
        Logger::debug<LogPrefix::IMU>("Read MGM values: (" + std::to_string(mx) + ", " + std::to_string(my) + ", " + std::to_string(mz) + ")");
        
        return { 
                { Axis::X, mx }, 
                { Axis::Y, my }, 
                { Axis::Z, mz } 
        };
    }

//     std::array<float, 3> IMU::read_gyrometer() {
//         float gx = 0, gy = 0, gz = 0;
// #ifdef RASPBERRY_PI
//         mpu.readGyrometer(gx, gy, gz);
// #endif // RASPBERRY_PI
//         return { gx, gy, gz };
//     }

//     std::array<float, 3> IMU::read_accelerometer() {
//         float ax = 0, ay = 0, az = 0;
// #ifdef RASPBERRY_PI
//         mpu.readAccelerometer(ax, ay, az);
// #endif // RASPBERRY_PI
//         return { ax, ay, az };
//     }
}