#ifndef _EPFLEURY_HPP
#define _EPFLEURY_HPP

#include <list>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

class EPFleury {
public:
	EPFleury();
	EPFleury(int count);
	~EPFleury();

	void addEdge(int a, int b);
	void removeEdge(int a, int b);
	std::vector<int>* buildPath();
	std::vector<int>* getPath();
	int DFSCount(int vertex, bool visited[]);
	bool isValidEdge(int a, int b);
	void printAdjacent();
	void _build(int current);

	int count;
	std::list<int> * adjacent;
	std::vector<int> * path;
};

#endif
