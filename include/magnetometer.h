#include "../lib/MPU/src/MPU9250_Master_I2C.h"
#include <memory>
#include <array>

namespace Satellite::Modules {
    class Magnetometer {
    private:
        std::unique_ptr<MPU9250_Master_I2C> mpu;
        std::array<std::array<float, 3>, 3> values;
        int errorCode;
    public:
        Magnetometer();
        void calibrate_magnetometer();
        void read_magnetometer();
        void read_gyrometer();
        void read_accelerometer();
        int get_error_code() const;
    };
}