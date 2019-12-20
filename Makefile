COMPILER    = g++
LOGGING     = -D'log(...)=printf(__VA_ARGS__)' -include cstdio
NO_LOGGING  = -D'log(...)' -Wno-unused-value
FLAGS       = -s -g -O3 -std=c++2a -Wall $(LOGGING)
IFLAGS      = -Iinclude
LFLAGS      = 
SRC         = \
	src/satellite.cpp \
	src/properties.cpp
OBJS        = $(SRC:.cpp=.o)
LIBS        = 
MAIN        = satellite
OUT         = $(MAIN)

all: $(MAIN)

$(MAIN): $(OBJS)
		@rm -f $(OUT)
		$(COMPILER) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LFLAGS) $(LIBS)
		@rm -f $(OBJS)

.cpp.o:
		@$(COMPILER) $(IFLAGS) $(FLAGS) -c $< -o $@
		
