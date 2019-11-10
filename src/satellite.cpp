/*
    Created by Maor Gershman, 9.9.2019
    ---
    This file will contain the satellite class.
*/

#include <satellite.hpp>
#include <logger.hpp>
#include <properties.hpp>
#include <client.hpp>

inline void clear_screen() {
    system("clear");
}

Satellite::Satellite() {
    clear_screen();
    Logger::verbose<LogPrefix::GENERAL>("Created the satellite instance!");
}

Satellite::~Satellite() {
    Logger::verbose<LogPrefix::GENERAL>("Destroyed the satellite instance!");
}

void Satellite::initialize() {
    Properties::reload();

    try {
        Modules::initialize(imu, magnetorquer);
    } catch (const std::runtime_error& error) {
        throw error;
    }

    Logger::info<LogPrefix::GENERAL>("Satellite is alive!");
}

void Satellite::run() {
    Client client;

    try {
        // As long as there are no UNRECOVERABLE ERRORS, reconnect.
        while (true) {
            client.start_connection();
            client.communicate(imu, magnetorquer);
            client.cleanup();
        }
    } catch (const std::runtime_error& error) {
        Logger::error<LogPrefix::CLIENT>(error.what());
        throw error;
    }
}

void Satellite::cleanup() {
    Logger::verbose<LogPrefix::GENERAL>("Cleaning up!");

    try {
        magnetorquer.cleanup();
    } catch (const std::runtime_error& error) {
        Logger::error<LogPrefix::CLIENT>(error.what());
        throw error;
    }

    Logger::verbose<LogPrefix::GENERAL>("All cleaned up!");
}