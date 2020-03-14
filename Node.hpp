#ifndef NODE_HPP
#define NODE_HPP

#include <cstdlib>
#include <vector>
#include <iostream>

class Node {
public:
	Node();
	Node(int x, int y, int id);
	
	void addEdge(int n);
	void removeOneEdge(int removeId);

	int x;
	int y;
	int id;
	std::vector<int> edges;
};

#endif
