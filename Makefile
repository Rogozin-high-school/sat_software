COMPILER_SAT_DEMO  = arm-linux-gnueabihf-g++ -marm -mfpu=vfp
PROPERTIES_FILE    = properties
FLAGS              = -s -O3 -std=gnu++17 -Wall -Wno-unused-variable \
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
OBJS               = $(SRC:.cpp=.o)

build-sat-demo: $(OBJS)
	@rm -f $(OUT)
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
	@rm -f $(OBJS)

run-sat-demo:
	@ssh ${host} 'rm -rf *'
	@scp -q $(PROPERTIES_FILE) $(OUT) ${host}:~/
	@gnome-terminal --full-screen -- ssh ${host} 'export TERM=xterm; sudo ./$(OUT); read' 2>/dev/null

.cpp.o:
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) -c $< -o $@