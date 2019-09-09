/*
    Created by Maor Gershman, 6.9.2019
    ---
    This file will contain the satellite class.
*/

#pragma once

#include "main.h"
#include "helper.h"
#include "logger.h"
#include "client.h"

#ifdef RASPBERRY_PI
#include "imu.h"
#else
#include "fakeimu.h"
#endif

namespace SatelliteSoftware {
    class Satellite {
    private:
        int propExitCode;
    public:
        const int& exitCode = propExitCode;

        Satellite() {
            Helper::clear_screen();
            Helper::print_date();
            Logger::debug("Satellite is alive!");

            // Create the client and connect to the ground station.
            Client client;
            if (client.socketFailed) {
                propExitCode = 1;
                return;
            }

            // Load the IMU (or the fake one).
            #ifdef RASPBERRY_PI
            IMU imu;
            #else
            FakeIMU imu;
            #endif
        }

        ~Satellite() {
            Logger::debug("Satellite is dead!");
        }
    };
}