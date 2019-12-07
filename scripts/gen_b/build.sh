home=$(dirname "$0")/../..

cd $home

arm-linux-gnueabihf-g++-9                           \
    -marm -march=armv6 -mfpu=vfp                    \
    -D RASPBERRY_PI                                 \
    -Iinclude                                       \
    -Ilib/WiringPi                                  \
    -Ilib/CrossPlatformDataBus                      \
    -Ilib/MPU                                       \
    -Lbin/link                                      \
    src/*.cpp                                       \
    src/modules/*.cpp                               \
    src/modules/imu/*.cpp                           \
    src/modules/magnetorquer/*.cpp                  \
    -o bin/satellite.out                            \
    -s -g -O0 -std=c++17                            \
    -lMPU -lwiringPi -lpthread

# TODO: Copy to satellite