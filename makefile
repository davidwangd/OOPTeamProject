all: main

CXXFLAGS = -std=c++11 -g

main: main.o CPPFileProcessor.o CPPToken.o CPPDetector.o Analysis.o utils/utils.a
	g++ $^ -o $@ $(CXXFLAGS)   
