/*
    Created by Maor Gershman, 9.9.2019
    ---
    This file will contain the satellite class.
*/

#include <raspberry_pi/raspberry_pi.hpp>
#include <satellite.hpp>
#include <logger.hpp>
#include <client.hpp>

Satellite::Satellite() {
    Helper::clear_screen();
    Helper::print_date();
    Logger::debug("Satellite is alive!");

    #ifdef RASPBERRY_PI
    RaspberryPi::initialize();
    #endif
}

Satellite::~Satellite() {
    Logger::debug("Satellite is dead!");
}

void Satellite::run() const {
    IMU imu;
    Torquer torq;
    Client client;

    try {
        imu.initialize();
    } catch (const std::runtime_error& error) {
        Logger::error(error.what(), LogPrefix::IMU);
        throw error;
    }

    try {
        // As long as there are no UNRECOVERABLE ERRORS, reconnect.
        while (true) {
            client.start_connection();
            client.communicate(imu, torq);
            client.cleanup();
        }
    } catch (const std::runtime_error& error) {
        Logger::error(error.what(), LogPrefix::CLIENT);
        throw error;
    }
}