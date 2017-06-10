all: utils.a

CXXFLAGS = -O2 -std=c++11

SOURCES = dependency.cpp dependency.h regex.cpp regex.h CPP_Language/CPPLexer.cpp CPP_Language/CPPLexer.h
utils.a: dependency.o regex.o lexer.o
	ar r utils.a dependency.o regex.o lexer.o

dependency.o: dependency.cpp

regex.o: regex.cpp

lexer.o: CPP_Language/CPPLexer.cpp
	g++  $(CXXFLAGS) CPP_Language/CPPLexer.cpp -c -o lexer.o