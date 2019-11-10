#include <modules/modules.hpp>
#include <logger.hpp>
#ifdef RASPBERRY_PI
#include <wiringPi.h>
#endif // RASPBERRY_PI

namespace Modules {
    inline void initialize_wiring_pi() {
#ifdef RASPBERRY_PI
        wiringPiSetup();
#endif // RASPBERRY_PI
    }

    void initialize(IMU& imu, Magnetorquer& magnetorquer) {
        initialize_wiring_pi();

        try {
            imu.initialize();
        } catch (const std::runtime_error& error) {
            Logger::error<LogPrefix::IMU>(error.what());
            throw error;
        }

        try {
            magnetorquer.initialize();
        } catch (const std::runtime_error& error) {
            Logger::error<LogPrefix::MAGNETORQUER>(error.what());
            throw error;
        }
    }

    void cleanup(Magnetorquer& magnetorquer) {
        try {
            magnetorquer.cleanup();
        } catch (const std::runtime_error& error) {
            Logger::error<LogPrefix::MAGNETORQUER>(error.what());
            throw error;
        }
    }
}