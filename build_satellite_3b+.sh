pi="pi@10.17.110.$1"

cd bin_satellite

arm-linux-gnueabihf-g++-9                      \
-D RASPBERRY_PI                                \
-I../include -I../lib                          \
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
    rm  -rf $pi:~/sat_software_cpp
    
sshpass -p "raspberry" \
    scp -r properties $pi:~/sat_software_cpp/
    
sshpass -p "raspberry" \
    scp -r bin_satellite/ $pi:~/sat_software_cpp/
    
sshpass -p "raspberry" \
    ssh -t $pi "cd ~/sat_software_cpp/bin_satellite && \
                g++ *.o -lpthread -lwiringPi"
