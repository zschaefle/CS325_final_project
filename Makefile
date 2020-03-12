CC=g++

all: tsp_program

tsp_program: tsp_program.cpp Node.o Link.o LinkSentenel.o BNB.o
	$(CC) -std=c++11 -g tsp_program.cpp Node.o Link.o LinkSentenel.o -o tsp_program

Node.o: Node.hpp Node.cpp
	$(CC) -std=c++11 -c Node.cpp -g

Link.o: Link.hpp Link.cpp Node.o
	$(CC) -std=c++11 -c Link.cpp -g

LinkSentenel.o: LinkSentenel.hpp LinkSentenel.cpp Link.o Node.o
	$(CC) -std=c++11 -c LinkSentenel.cpp -g

BNB.o: bound_and_branch.hpp bound_and_branch.cpp Link.o Node.o
	$(CC) -std=c++11 -c bound_and_branch.cpp -g
clean:
	rm -f tsp_program *.o
