COMPILER_SAT_DEMO  = arm-linux-gnueabihf-g++ -marm -mfpu=vfp
COMPILER_DEMO      = g++
PROPERTIES_FILE    = properties
FLAGS              = -s -O3 -std=gnu++17 -Wall -Wno-unused-variable \
    -D LOGGING \
    -D LOGGING_FUNCTION_CALLS \
    -D PROPERTIES_FILE=\"$(PROPERTIES_FILE)\"
IFLAGS             = -Iinclude -Iinclude/subsystems
LFLAGS             = -static-libstdc++
LIBS               =
OUT                = satellite
SRC                = \
	src/satellite.cpp \
	src/properties.cpp \
	src/subsystems/subsystems.cpp

build-demo:
	@$(COMPILER_DEMO) $(IFLAGS) $(FLAGS) $(SRC) -o $(OUT) $(LIBS) $(LFLAGS)

build-sat-demo:
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) $(SRC) -o $(OUT) $(LIBS) $(LFLAGS)
	@scp -q $(PROPERTIES_FILE) $(OUT) ${host}:~/
	@rm -f $(OUT)

run-sat-demo:
	@gnome-terminal --maximize -- ssh ${host} 'export TERM=xterm; sudo ./$(OUT); read'