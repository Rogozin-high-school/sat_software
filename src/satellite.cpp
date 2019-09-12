/*
    Created by Maor Gershman, 9.9.2019
    ---
    This file will contain the satellite class.
*/

#include "../include/satellite.h"
#include "../include/logger.h"
#include "../include/client.h"

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

        // Load the IMU (the real or the fake one).
        IMU imu;

        // Actually communicate with the ground station
        client.communicate(imu);
    }

    Satellite::~Satellite() {
        Logger::debug("Satellite is dead!");
    }
}