#include "../include/magnetometer.h"
#include <wiringPi.h>

namespace Satellite::Modules {
    Magnetometer::Magnetometer() {
        wiringPiSetup();
        mpu = std::make_unique<MPU9250_Master_I2C>
            (MPU9250_Master_I2C::AFS_2G,
            MPU9250_Master_I2C::GFS_250DPS, 
            MPU9250_Master_I2C::MFS_16BITS, 
            MPU9250_Master_I2C::M_8Hz);
        // Start the MPU9250
        errorCode = mpu->begin();
    }

    void Magnetometer::calibrate_magnetometer() {
        mpu->calibrateMagnetometer();
    }

    void Magnetometer::read_magnetometer() {
        mpu->readMagnetometer(values[0][0], values[0][1], values[0][2]);
    }

    void Magnetometer::read_gyrometer() {
        mpu->readGyrometer(values[1][0], values[1][1], values[1][2]);
    }

    void Magnetometer::read_accelerometer() {
        mpu->readAccelerometer(values[2][0], values[2][1], values[2][2]);
    }

    int Magnetometer::get_error_code() const {
        return errorCode;
    }
}