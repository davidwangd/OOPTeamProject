all: calculate.exe
calculate.exe: polynomial.o posynomial.o main.o func.h
	g++ polynomial.o posynomial.o main.o -o calculate.exe
polynomial.o: polynomial.cpp func.h
	g++ -c polynomial.cpp -o polynomial.o
posynomial.o: posynomial.cpp func.h
	g++ -c posynomial.cpp -o posynomial.o
main.o: main.cpp func.h
	g++ -c main.cpp -o main.o
clean:
	del *.o *.exe
