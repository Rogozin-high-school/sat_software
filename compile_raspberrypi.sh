g++-9.1 src/*.cpp \
        modules/magnetometer/magnetometer.cpp \
        modules/magnetometer/MPU/src/MPU.cpp \
        modules/magnetometer/MPU/src/MPU9250.cpp \
        modules/magnetometer/MPU/src/MPU9250_Master.cpp \
        modules/magnetometer/MPU/src/MPU9250_Master_I2C.cpp \
        modules/magnetometer/CrossPlatformDataBus/extras/i2c/wiringpi/src/WiringPiI2C.cpp \
        -s -std=c++17 -O3 \
        -lpthread -lwiringPi