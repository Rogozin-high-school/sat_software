time g++-9.1 -Iinclude                              \
        -Ilib                                       \
        src/*.cpp                                   \
        src/modules/imu/*.cpp                       \
        src/modules/magnetorquer/*.cpp              \
        lib/MPU/MPU.cpp                             \
        lib/MPU/MPU9250.cpp                         \
        lib/MPU/MPU9250_Master.cpp                  \
        lib/MPU/MPU9250_Master_I2C.cpp              \
        lib/CrossPlatformDataBus/WiringPiI2C.cpp    \
        -s -std=c++17 -O3                           \
        -D RASPBERRY_PI                             \
        -lpthread -lwiringPi
