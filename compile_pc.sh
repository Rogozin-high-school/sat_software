time g++ -Iinclude                      \
         src/*.cpp                      \
         src/modules/imu/*.cpp          \
         src/modules/magnetorquer/*.cpp \
         -s -std=c++17                  \
         -lpthread
