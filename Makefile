CC=g++

all: tsp_program

tsp_program: tsp_program.cpp Node.o Link.o LinkSentenel.o HeldKarpSolver.o TwoOpt.o EPFleury.o Christofides.o edgeMethods.o
	$(CC) -std=c++11 -g tsp_program.cpp Node.o Link.o LinkSentenel.o HeldKarpSolver.o TwoOpt.o EPFleury.o Christofides.o edgeMethods.o -o tsp_program

LinkSentenel.o: LinkSentenel.hpp LinkSentenel.cpp Link.hpp Node.hpp
	$(CC) -std=c++11 -c LinkSentenel.cpp -g

Link.o: Link.hpp Link.cpp Node.hpp
	$(CC) -std=c++11 -c Link.cpp -g

Node.o: Node.hpp Node.cpp
	$(CC) -std=c++11 -c Node.cpp -g

EPFleury.o: EPFleury.hpp EPFleury.cpp
	$(CC) -std=c++11 -c EPFleury.cpp -g

Christofides.o: Christofides.hpp Node.hpp EPFleury.hpp Christofides.cpp
	$(CC) -std=c++11 -c Christofides.cpp -g

HeldKarpSolver.o: HeldKarpSolver.hpp HeldKarpSolver.cpp
	$(CC) -std=c++11 -c HeldKarpSolver.cpp -g

TwoOpt.o: TwoOpt.hpp TwoOpt.cpp
	$(CC) -std=c++11 -c TwoOpt.cpp -g

edgeMethods.o: Node.hpp edgeMethods.hpp edgeMethods.cpp
	$(CC) -std=c++11 -c edgeMethods.cpp -g

clean:
	rm -f tsp_program *.o
