COMPILER_SAT_DEMO  = arm-linux-gnueabihf-g++ -marm -mfpu=vfp
PROPERTIES_FILE    = properties
FLAGS              = -s -g -O0 -std=gnu++17 -Wall -Wno-unused-variable -include stdexcept \
	-D LOGGING \
	-D LOGGING_FUNCTION_CALLS \
	-D PROPERTIES_FILE=\"$(PROPERTIES_FILE)\"
IFLAGS             = -Iinclude -Iinclude/subsystems
LFLAGS             = -static
LIBS               = 
OUT                = satellite
SRC                = \
	src/satellite.cpp \
	src/properties.cpp \
	src/subsystems/subsystems.cpp

build-demo:
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) $(SRC) -o $(OUT) $(LIBS) $(LFLAGS)
	@scp -q $(PROPERTIES_FILE) $(OUT) ${host}:~/
	@rm -f $(OUT)

run-demo:
	@gnome-terminal --maximize -- ssh ${host} 'export TERM=xterm; sudo ./$(OUT); read'