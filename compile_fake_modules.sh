cd bin/modules/fake
time g++ -I../../../include                                    \
         ../../../src/modules/modules.cpp                      \
         ../../../src/modules/imu/*.cpp                        \
         ../../../src/modules/magnetorquer/*.cpp               \
         -c -s -std=c++17 -O3                                  
rm -f bin/a.out