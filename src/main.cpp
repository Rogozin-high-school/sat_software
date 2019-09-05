/*
    Created by Maor Gershman, 25.8.2019
    ---
    This is the entry point of the satellite app.
    This file should be as short and precise as possible.
*/

#include "../include/logger.h"
#include "../include/client.h"
#include "../modules/magnetometer/magnetometer.h"

int main(void) {
    Satellite::Logger::log("Starting the satellite!");

    // Start the client
    Satellite::Client client;
    if (client.failure()) {
        Satellite::Logger::log("Connection has failed!");
        return -1;
    }
    Satellite::Logger::log("Client connected!");

    // Start the magnetometer
    Satellite::Modules::Magnetometer magnetometer;
    int code = magnetometer.get_error_code();
    switch (code) {
    case MPUIMU::ERROR_IMU_ID:
        Satellite::Logger::log("Bad IMU device ID!");
        return code;
    case MPUIMU::ERROR_MAG_ID:
        Satellite::Logger::log("Bad magnetometer device ID!");
        return code;
    case MPUIMU::ERROR_SELFTEST:
        Satellite::Logger::log("Failed self test!");
        return code;
    default:
        Satellite::Logger::log("MPU9250 online!");
    }
    
    return 0;
}
