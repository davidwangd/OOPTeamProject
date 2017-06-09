SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, ../%.o, $(SOURCES))
CXXFLAGS = -std=c++11

all: $(OBJECTS)

clean:
	rm -f *.o

clean2:
	del *.o