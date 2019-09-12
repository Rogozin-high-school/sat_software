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

        // Load the IMU (the real or the fake one).
        IMU imu;
        if (!imu.allOk) {
            propExitCode = 1;
            return;
        }

        // Reconnect everytime something goes wrong!
        while (true) {
            Client client;
            if (client.start_connection()) {
                client.communicate(imu);
            }
        }
    }

    Satellite::~Satellite() {
        Logger::debug("Satellite is dead!");
    }
}