INC=-I.
CXX=clang++-5.0
CXXFLAGS=-std=c++17 ${INC}

all: main

main: cli.o mc.o utils.o ml.o

cli.o: cli.cpp
	${CXX} -MMD -c -o $@ $< $(CXXFLAGS)

utils.o: utils.cpp
	${CXX} -MMD -c -o $@ $< $(CXXFLAGS)

mc.o: mc.cpp
	${CXX} -MMD -c -o $@ $< $(CXXFLAGS)

ml.o: ml.cpp
	${CXX} -MMD -c -o $@ $< $(CXXFLAGS)

-include *.d
