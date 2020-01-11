COMPILER_SAT_DEMO  = arm-linux-gnueabihf-g++ -march=armv6 -marm -mfpu=vfpv2 -no-pie -fPIC
PROPERTIES_FILE    = properties
IFLAGS             = \
	-Ilib/CrossPlatformDataBus/src \
	-Ilib/WiringPi/wiringPi \
	-Iinclude \
	-Iinclude/Components \
	-Iinclude/SubSystems
FLAGS              = \
	-s -O3 -std=gnu++17 -Wall -Wno-unused-variable \
	-include include/Logger.hpp \
    -D PROPERTIES_FILE=\"$(PROPERTIES_FILE)\" \
	-D LOGGING \
	-D LOGGING_FUNCTION_CALLS
LIBS               = \
	-lwiringPi \
	-lpthread
LFLAGS             = \
	-Llib/WiringPi/wiringPi
OUT                = satellite
SRC                = \
	lib/CrossPlatformDataBus/extras/i2c/wiringpi/src/WiringPiI2C.cpp \
	lib/MPU/src/MPU.cpp \
	lib/MPU/src/MPU9250.cpp \
	lib/MPU/src/MPU9250_Master.cpp \
	lib/MPU/src/MPU9250_Master_I2C.cpp \
	src/Satellite.cpp \
	src/Properties.cpp \
	src/Components.cpp \
	src/Components/IMU.cpp \
	src/SubSystems.cpp \
	src/SubSystems/Communication.cpp \
	src/SubSystems/Telemetry.cpp \
	src/SubSystems/Maneuvering.cpp
OBJS               = $(SRC:.cpp=.o)

build-sat-demo: $(OBJS)
	@rm -f $(OUT)
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
	@rm -f $(OBJS)

load-sat-demo:
	@scp -q $(PROPERTIES_FILE) $(OUT) sat-demo:~/

load-libs:
	@rm -rf lib
	@git clone https://github.com/Rogozin-high-school/WiringPi.git lib/WiringPi
	@git clone https://github.com/Rogozin-high-school/CrossPlatformDataBus.git lib/CrossPlatformDataBus
	@git clone https://github.com/Rogozin-high-school/MPU.git lib/MPU
	@cd lib/WiringPi/wiringPi && make && make clean

clean:
	@rm -rf $(OUT) $(OBJS)

.cpp.o:
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) -c $< -o $@