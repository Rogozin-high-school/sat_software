COMPILER         = g++
FLAGS            = -s -O3 -std=gnu++2a -Wall -include logger.hpp -include stdexcept -D LOGGING -D LOGGING_FUNCTION_CALLS
IFLAGS           = -Iinclude -Iinclude/subsystems
LIBS             = -lpthread
OUT              = satellite
SRC              = \
	src/satellite.cpp \
	src/properties.cpp \
	src/subsystems/subsystems.cpp

all:
	$(COMPILER) $(IFLAGS) $(FLAGS) $(SRC) -o $(OUT) $(LFLAGS) $(LIBS)
