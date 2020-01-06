COMPILER_SAT_DEMO  = arm-linux-gnueabihf-g++ -march=armv6 -marm -mfpu=vfpv2 -no-pie
PROPERTIES_FILE    = properties
FLAGS              = -s -O3 -std=gnu++17 -Wall -Wno-unused-variable \
    -D LOGGING \
    -D LOGGING_FUNCTION_CALLS \
    -D PROPERTIES_FILE=\"$(PROPERTIES_FILE)\"
IFLAGS             = -Iinclude -Iinclude/subsystems
LFLAGS             = -static-libstdc++
OUT                = satellite
SRC                = \
	src/satellite.cpp \
	src/properties.cpp \
	src/subsystems.cpp \
	src/subsystems/communication.cpp
OBJS               = $(SRC:.cpp=.o)

build-sat-demo: $(OBJS)
	@rm -f $(OUT)
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
	@rm -f $(OBJS)

load-sat-demo:
	@scp -q $(PROPERTIES_FILE) $(OUT) sat-demo:~/

run-sat-demo:
	@gnome-terminal --full-screen -- ssh sat-demo 'sudo ./$(OUT); read' 2>/dev/null

clean:
	@rm -rf $(OUT) $(OBJS)

.cpp.o:
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) -c $< -o $@