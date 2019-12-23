COMPILER         = g++
FLAGS            = -s -O0 -std=gnu++17 -Wall -include stdexcept -D LOGGING -D LOGGING_FUNCTION_CALLS
IFLAGS           = -Iinclude -Iinclude/subsystems
OUT              = satellite
SRC              = \
	src/satellite.cpp \
	src/properties.cpp \
	src/subsystems/subsystems.cpp

all:
	$(COMPILER) $(IFLAGS) $(FLAGS) $(SRC) -o $(OUT) $(LIBS)
