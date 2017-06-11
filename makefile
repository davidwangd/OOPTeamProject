all: PlagiarismDetector.exe

CXX = g++
CC = g++
CXXFLAGS = -std=c++11 -g -DDEBUG

PlagiarismDetector.exe: main.o analyzer.o CPPDetector.o CPPFileProcessor.o CPPToken.o utils/utils.a FileProcessor.o Detector.o
	g++ $(CXXFLAGS) -o PlagiarismDetector.exe $^ 

clean:
	rm -f *.o *.exe

utils/utils.a: utils/dependency.o utils/FileEnumerator.o utils/lexer.o utils/regex.o
	ar r $@ $^

utils/lexer.o: utils/CPP_Language/CppLexer.h utils/CPP_Language/CPPLexer.cpp 
	g++ $(CXXFLAGS) utils/CPP_Language/CppLexer.cpp -c -o utils/lexer.o