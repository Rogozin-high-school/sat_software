cd bin/lib
time g++ -I../../lib                                       \
         -D RASPBERRY_PI                                   \
         -m32                                              \
         ../../lib/MPU/MPU.cpp                             \
         ../../lib/MPU/MPU9250.cpp                         \
         ../../lib/MPU/MPU9250_Master.cpp                  \
         ../../lib/MPU/MPU9250_Master_I2C.cpp              \
         ../../lib/CrossPlatformDataBus/WiringPiI2C.cpp    \
         -c -s -O3
