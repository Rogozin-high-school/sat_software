echo Enter satellite IP...

read ip

cd bin_satellite

time \
arm-linux-gnueabihf-g++-9 \
-D RASPBERRY_PI \
-I../include \
-I../lib \
../lib/MPU/MPU.cpp                             \
../lib/MPU/MPU9250.cpp                         \
../lib/MPU/MPU9250_Master.cpp                  \
../lib/MPU/MPU9250_Master_I2C.cpp              \
../lib/CrossPlatformDataBus/WiringPiI2C.cpp    \
../src/modules/modules.cpp                     \
../src/modules/imu/*.cpp                       \
../src/modules/magnetorquer/*.cpp              \
../src/*.cpp                                   \
-c -s -std=c++17 -O3

cd ..

sshpass -p "raspberry" \
rm -rf pi@$ip:~/sat_software_cpp/bin_satellite/

sshpass -p "raspberry" \
scp -r bin_satellite/ pi@$ip:~/sat_software_cpp/

sshpass -p "raspberry" \
ssh -t pi@$ip "cd ~/sat_software_cpp/bin_satellite && g++ *.o -lpthread -lwiringPi"
