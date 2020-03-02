CC=g++

all: tsp_program

tsp_program: tsp_program.cpp Node.o
	$(CC) -std=c++11 -g tsp_program.cpp Node.o -o tsp_program

Node.o: Node.hpp Node.cpp
	$(CC) -std=c++11 -c Node.cpp -g

clean:
	rm -f tsp_program *.o