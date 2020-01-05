# COMPILER_DEMO      = g++
COMPILER_SAT_DEMO  = arm-linux-gnueabihf-g++ -marm -mfpu=vfp
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
OBJS               = $(SRC:.cpp=.o)

# build-demo: $(OBJS)
# 	@rm -f $(OUT)
# 	@$(COMPILER_DEMO) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
# 	@rm -f $(OBJS)

build-sat-demo: $(OBJS)
	@rm -f $(OUT)
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
	@rm -f $(OBJS)

run-sat-demo: $(OBJS)
	@ssh ${host} 'rm -r *'
	@scp -q $(PROPERTIES_FILE) $(OUT) ${host}:~/
	@rm -f $(OUT)
	@gnome-terminal --maximize -- ssh ${host} 'export TERM=xterm; sudo ./$(OUT); read'

.cpp.o:
#	@$(COMPILER_DEMO) $(IFLAGS) $(FLAGS) -c $< -o $@
	@$(COMPILER_SAT_DEMO) $(IFLAGS) $(FLAGS) -c $< -o $@