/*
    Created by Maor Gershman, 25.8.2019
    ---
    This is the entry point of the satellite app.
    This file should be as short and precise as possible.
*/

#include "../include/main.h"
#include "../include/logger.h"
#include "../include/client.h"

// Include these modules ONLY for Raspberry Pi!
#ifdef RASPBERRY_PI
#include "../include/magnetometer.h"
#endif

int main(void) {
    Satellite::Logger::debug("Satellite is alive!");

    // Start the client
    Satellite::Client client;
    if (client.failure()) {
        Satellite::Logger::error("Connection has failed!", Satellite::Logger::LogPrefix::CLIENT);
        return -1;
    }
    Satellite::Logger::info("Connected!", Satellite::Logger::LogPrefix::CLIENT);

    // Start the magnetometer (if running on Raspberry Pi)
    #ifdef RASPBERRY_PI
    Satellite::Modules::Magnetometer magnetometer;
    int code = magnetometer.get_error_code();
    switch (code) {
    case MPUIMU::ERROR_IMU_ID:
        Satellite::Logger::severe("Bad IMU device ID!", Satellite::Logger::LogPrefix::MAGNETOMETER);
        return code;
    case MPUIMU::ERROR_MAG_ID:
        Satellite::Logger::severe("Bad magnetometer device ID!", Satellite::Logger::LogPrefix::MAGNETOMETER);
        return code;
    case MPUIMU::ERROR_SELFTEST:
        Satellite::Logger::severe("Failed self test!", Satellite::Logger::LogPrefix::MAGNETOMETER);
        return code;
    default:
        Satellite::Logger::debug("MPU9250 online!", Satellite::Logger::LogPrefix::MAGNETOMETER);
    }
    #endif
    
    Satellite::Logger::debug("Satellite is dead!");
    return 0;
}
