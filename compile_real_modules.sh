cd bin/modules/real
time g++ -I../../../include                                    \
         -I../../../lib                                        \
         -D RASPBERRY_PI                                       \
         -m32                                                  \
         ../../../src/modules/modules.cpp                      \
         ../../../src/modules/imu/*.cpp                        \
         ../../../src/modules/magnetorquer/*.cpp               \
         -c -s -std=c++17 -O3                                  
rm -f bin/a.out
