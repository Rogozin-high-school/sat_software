home=$(dirname "$0")/../..

cd $home
mkdir -p bin/link
mkdir lib_raw
cd lib_raw

git clone https://github.com/Rogozin-high-school/WiringPi.git
git clone https://github.com/Rogozin-high-school/CrossPlatformDataBus.git
git clone https://github.com/Rogozin-high-school/MPU.git

cd WiringPi/wiringPi
make static
# sudo make install-static
mv libwiringPi.a ../../../bin/link

cd ../..

arm-linux-gnueabihf-g++-9                                               \
    -marm -march=armv6 -mfpu=vfp                                        \
    -ICrossPlatformDataBus/src                                          \
    -IWiringPi/wiringPi                                                 \
    CrossPlatformDataBus/extras/i2c/wiringpi/src/WiringPiI2C.cpp        \
    MPU/src/MPU.cpp                                                     \
    MPU/src/MPU9250.cpp                                                 \
    MPU/src/MPU9250_Master.cpp                                          \
    MPU/src/MPU9250_Master_I2C.cpp                                      \
    -c -std=c++17 -fPIC

ar rcs libMPU.a *.o
ranlib libMPU.a
rm -f *.o
mv libMPU.a ../bin/link

cd ..
rm -rf lib_raw
clear