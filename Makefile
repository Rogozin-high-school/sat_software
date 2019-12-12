COMPILER    = arm-linux-gnueabihf-g++-9
FLAGS       = -s -g -Wall -std=c++17 -marm -mfpu=vfp
IFLAGS      = -Iinclude
LFLAGS      = -Llib
SRC         = src/*.cpp
OBJS        = $(SRC:.cpp=.o)
LIBS        =
MAIN        = satellite
OUT         = $(MAIN)

all: $(MAIN)

$(MAIN): $(OBJS)
		$(RM) $(OUT)
		$(COMPILER) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LFLAGS) $(LIBS)
		$(RM) $(OBJS)

.cpp.o:
		$(COMPILER) $(IFLAGS) $(FLAGS) -c $< -o $@
		