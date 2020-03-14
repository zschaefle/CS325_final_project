#ifndef CHRISTOFIDES_HPP
#define CHRISTOFIDES_HPP

#include <cstdio>
#include <iostream>
#include "EPFleury.hpp"
#include "edgeMethods.hpp"
#include "Node.hpp"

class Christofides {
public:
	Christofides(int ** E, Node * V, int count);
	~Christofides();
	void genMSTEdges();
	void perfectMatchMultigraph();
	int* makeHamFromEul(std::vector<int>* Euler);
	int* makeChristofidesTour();
	int* findSmallestAvailable(int* treeArr);
	int* findSmallestConnected(int* treeArr);
	int unconnectedCount(int * treeArr, int size);

	int ** E;
	Node * V;
	int count;
	EPFleury* epf;
};

#endif