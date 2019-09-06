/*
    Created by Maor Gershman, 6.9.2019
    ---
    This file will contain the satellite class.
*/

#pragma once

#include "main.h"
#include "logger.h"
#include "client.h"

#ifdef RASPBERRY_PI
#include "magnetometer.h"
#endif

namespace SatelliteSoftware {
    class Satellite {
    private:
        int exCode = 0;
    public:
        const int& exitCode = exCode;

        Satellite() {
            Logger::print_date();
            Logger::debug("Satellite is alive!");

            // Create the client and connect to the ground station. 
            Client client;
            if (client.socketFailed) {
                exCode = 1;
                return;
            }

            // Load the magnetometer.
            #ifdef RASPBERRY_PI
            Magnetometer magnetometer;
            #endif
        }

        ~Satellite() {
            Logger::debug("Satellite is dead!");
        }
    };
}