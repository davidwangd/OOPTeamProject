all: PlagiarismDetector.exe

CXX = g++
CC = g++
CXXFLAGS = -std=c++11 -g -DDEBUG

PlagiarismDetector.exe: main.o analyzer.o CPPDetector.o CPPFileProcessor.o CPPToken.o utils/utils.a FileProcessor.o Detector.o
	g++ $(CXXFLAGS) -o PlagiarismDetector.exe $^ 

clean:
	rm -f *.o *.exe
