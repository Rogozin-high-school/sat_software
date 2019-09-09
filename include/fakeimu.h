/*
    Created by Maor Gershman, 8.9.2019
    ---
    This class will fake the IMU, for testing on the PC.
*/

#pragma once

#ifndef RASPBERRY_PI
#include "logger.h"
#include <random>

namespace SatelliteSoftware {
    class FakeIMU {
    public:
        FakeIMU() {
            Logger::info("Ready!", Logger::Prefix::FAKEIMU);
        }

        void calibrate_magnetometer() {
            // Maybe will be used in the future.
        }

        std::array<float, 3> read_magnetometer() {
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
            return {mx, my, mz};
        }
        
        std::array<float, 3> read_gyrometer() {
            // Will be used later.
            return {0.0f, 0.0f, 0.0f};
        }
        
        std::array<float, 3> read_accelerometer() {
            // Will be used later.
            return {0.0f, 0.0f, 0.0f};
        }
    };
}
#endif // RASPBERRY_PI