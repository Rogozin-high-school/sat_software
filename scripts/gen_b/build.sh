home=$(dirname "$0")/../..

cd $home

time \
arm-linux-gnueabihf-g++-9                           \
    -marm -mfpu=vfp                                 \
    -D RASPBERRY_PI                                 \
    -Iinclude                                       \
    -Ilib/WiringPi                                  \
    -Ilib/CrossPlatformDataBus                      \
    -Ilib/MPU                                       \
    -Lbin                                           \
    src/*.cpp                                       \
    src/modules/*.cpp                               \
    src/modules/imu/*.cpp                           \
    src/modules/magnetorquer/*.cpp                  \
    -o bin/satellite                                \
    -s -g -O0 -std=c++17                            \
    -static                                         \
    -lMPU -lwiringPi -lpthread

scp bin/satellite pi:~/