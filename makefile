all: PlagiarismDetector.exe

CXX = g++
CC = g++
CXXFLAGS = -std=c++11 -g

PlagiarismDetector.exe: main.o analyzer.o CPPDetector.o CPPFileProcessor.o CPPToken.o utils/utils.a 
	g++ $(CXXFLAGS) -o PlagiarismDetector.exe $^ 
