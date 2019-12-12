COMPILER    = arm-linux-gnueabihf-g++-9 -marm -mfpu=vfp
DEFINES     = -D LOGGING
FLAGS       = -s -g -O3 -Wall -std=c++17 $(DEFINES)
IFLAGS      = -Iinclude
LFLAGS      = -Llib
SRC         = src/*.cpp
OBJS        = $(SRC:.cpp=.o)
LIBS        =
MAIN        = satellite
OUT         = bin/$(MAIN)

all: $(MAIN)

$(MAIN): $(OBJS)
		mkdir -p bin
		rm -f $(OUT)
		$(COMPILER) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LFLAGS) $(LIBS)
		rm -f $(OBJS)

.cpp.o:
		$(COMPILER) $(IFLAGS) $(FLAGS) -c $< -o $@
		