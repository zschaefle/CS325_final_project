#ifndef NODE_HPP
#define NODE_HPP

#include <cstdlib>

class Node {
public:
	Node();
	Node(int x, int y, int id);

	int x;
	int y;
	int id;
};

#endif
