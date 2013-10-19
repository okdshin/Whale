CXX = g++ -pg -std=gnu++11
CXXFLAGS = -O3 -Wall -g -D BIGNATURAL_UNIT_TEST -D__STRICT_ANSI__
INCLUDES = 
LIBS =
OBJS = BigNatural.o
PROGRAM = BigNatural.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
