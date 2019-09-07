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
#include "imu.h"

namespace SatelliteSoftware {
    class Satellite {
    private:
        int exCode = 0;
    public:
        const int& exitCode = exCode;

        Satellite() {
            Helper::clear_screen();
            Helper::print_date();
            Logger::debug("Satellite is alive!");

            // Create the client and connect to the ground station. 
            Client client("84.109.40.45", 8888);
            if (client.socketFailed) {
                exCode = 1;
                return;
            }

            // Load the IMU.
            #ifdef RASPBERRY_PI
            IMU imu;
            #endif // RASPBERRY_PI
        }

        ~Satellite() {
            Logger::debug("Satellite is dead!");
        }
    };
}