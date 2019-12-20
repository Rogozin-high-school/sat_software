COMPILER         = g++

ENABLE_LOGGING   = -D 'log(...) = printf(__VA_ARGS__)' -include cstdio
DISABLE_LOGGING  = -D 'log(...)' -Wno-unused-value
LOGGING          = $(ENABLE_LOGGING)

FLAGS            = -s -g -O3 -std=c++2a -Wall $(LOGGING)
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
