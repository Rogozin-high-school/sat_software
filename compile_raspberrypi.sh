g++-9.1 src/*.cpp \
        lib/MPU/src/MPU.cpp \
        lib/MPU/src/MPU9250.cpp \
        lib/MPU/src/MPU9250_Master.cpp \
        lib/MPU/src/MPU9250_Master_I2C.cpp \
        lib/CrossPlatformDataBus/extras/i2c/wiringpi/src/WiringPiI2C.cpp \
        -s -std=c++17 -O3 \
        -lpthread -lwiringPi