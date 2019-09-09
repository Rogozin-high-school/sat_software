/*
    Created by Maor Gershman, 9.9.2019
    ---
    This file will contain the satellite class.
*/

#include "../include/satellite.h"
#include "../include/logger.h"
#include "../include/client.h"

#ifdef RASPBERRY_PI
#include "../include/imu.h"
#else
#include "../include/fakeimu.h"
#endif

namespace SatelliteSoftware {
    Satellite::Satellite() : exitCode(propExitCode) {
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

    Satellite::~Satellite() {
        Logger::debug("Satellite is dead!");
    }
}