CXX = g++ -std=gnu++11 
CXXFLAGS = -g -Wall -D BENCHMARK_UNIT_TEST -DMULTIPLY_FFT
INCLUDES = 
LIBS =
OBJS = BenchMark.o
PROGRAM = BenchMark.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
