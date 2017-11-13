INC=-I.
CXXFLAGS=-std=c++11 ${INC}

all: main

main: cli.o

cli.o: cli.cpp
	${CXX} -MMD -c -o $@ $< $(CXXFLAGS)

-include *.d
