COMPILER         = g++
FLAGS            = -s -O3 -std=c++2a -Wall -include logger.hpp -D LOGGING
IFLAGS           = -Iinclude -Iinclude/subsystems
LFLAGS           = 
LIBS             = -lpthread
OUT              = satellite
SRC              = \
	src/satellite.cpp \
	src/properties.cpp \
	src/subsystems/subsystems.cpp

all:
	$(COMPILER) $(IFLAGS) $(FLAGS) $(SRC) -o $(OUT) $(LFLAGS) $(LIBS)
