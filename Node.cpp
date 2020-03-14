#include "Node.hpp"

Node::Node() {
	x = 0;
	y = 0;
	id = 0;
}

Node::Node(int xIn, int yIn, int idIn) {
	x = xIn;
	y = yIn;
	id = idIn;
}

void Node::addEdge(int n) {
	this->edges.push_back(n);
}

void Node::removeOneEdge(int removeId) {
	int removed = 0;
	std::vector<int> outputs;
	printf("looking for %d in node %d\n", removeId, this->id);
	for (int i = 0; i < this->edges.size(); i++) {
		printf("checking %d\n", this->edges[i]);
		if (this->edges[i] == removeId && removed == 0) {
			printf ("ignoring id %d from id %d\n", this->edges[i], this->id);
			removed = 1;
		} else {
			outputs.push_back(this->edges[i]);
		}
	}
	this->edges = outputs;
}
