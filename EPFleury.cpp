
#include "EPFleury.hpp"

EPFleury::EPFleury() {
	count = 0;
	adjacent = new std::list<int>[0];
	path = new std::vector<int>;
}

EPFleury::EPFleury(int count){
	this->count = count;
	adjacent = new std::list<int>[count];
	path = new std::vector<int>;
}

EPFleury::~EPFleury() {
	delete[] this->adjacent;
	delete this->path;
}

// NOTE: a lot of this code was retrieved/inspired by code at
// https://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/
// code was analysed to the point of understanding before being used

// "removes" an edge from a to b (and from b to a)
// by setting respective storing values to -1
void EPFleury::removeEdge(int a, int b) {
	std::list<int>::iterator i = std::find(adjacent[a].begin(), adjacent[a].end(), b);
	*i = -1;
	i = std::find(adjacent[b].begin(), adjacent[b].end(), a);
	*i = -1;
}

// Count the edges that have not yet been visited
int EPFleury::DFSCount(int vertex, bool visited[]) {
	visited[vertex] = true;
	int count = 1;

	// iterate through the adjacency lists of the given node
	// recursively call this on each adjacent node if it hasn't been visited
	std::list<int>::iterator i;
	for (i = adjacent[vertex].begin(); i != adjacent[vertex].end(); i++) {
		if (*i != -1 && !(visited[*i])) {
			count += DFSCount(*i, visited);
		}
	}
	return count;
}

// checker to see if a given edge is valid to continue to in generating
// the Eulerian Path
bool EPFleury::isValidEdge(int a, int b) {
	int countA = 0;
	std::list<int>::iterator i;
	// true if the node has 1 and only 1 edge
	for (i = adjacent[a].begin(); i != adjacent[a].end(); i++) {
		if (*i != -1) {
			countA++;
		}
	}
	if (countA == 1) {
		return true;
	}

	// otherwise, count "accessible" nodes
	bool visited[count];
	std::memset(visited, false, count);
	countA = DFSCount(a, visited);
	// count "accessible" nodes if the considered edge is removed
	removeEdge(a, b);
	std::memset(visited, false, count);
	int countB = DFSCount(a, visited);

	addEdge(a, b);

	// true if removing the edge does not affect
	// the overall accessibility, false if it cuts off a section
	return (countA > countB) ? false : true;
}

// a function I added for debugging
void EPFleury::printAdjacent() {
	std::list<int>::iterator i;
	for (int k = 0; k < count; k++) {
		for (i = adjacent[k].begin(); i != adjacent[k].end(); i++){
			std::cout << "k: " << k << "\telement: " << *i << std::endl;
		}
	}
}

// main function to build the path through Fleury's algorithm
// determins the start node, then calls a halper function
std::vector<int> * EPFleury::buildPath() {
	int start = 0;
	for (int i = 0; i < count; i++) {
		if (adjacent[i].size() % 2 == 1) {
			start = i;
			path->push_back(start);
			break;
		}
	}
	// std::cout << "starting at " << start << std::endl;
	_build(start);
	return this->path;
}

// functino that gets the path
std::vector<int> *EPFleury::getPath() {
	// if the path doesn't contain all the possible nodes, remake it
	if (path->size() < count) {
		// std::cout << "need to build before returning path. size = " << path->size() << " count = " << count << std::cout;
		path->resize(0);
		buildPath();
	}
	return path;
}

// helper for the build function
void EPFleury::_build(int current) {
	// for all nodes adjacent to current...
	std::list<int>::iterator i;
	for (i = adjacent[current].begin(); i != adjacent[current].end(); i++) {
		int vertex = *i;
		// if the edge is valid
		if (vertex != -1 && isValidEdge(current, vertex)) {
			// remove it, add it to the path and recurse to the considered vertex
			removeEdge(current, vertex);
			path->push_back(vertex);
			_build(vertex);
		}
	}
}

// function to add edges to the internal edge set
// requires externals to set up the edges of the multigraph to consider
void EPFleury::addEdge(int a, int b){
	adjacent[a].push_back(b);
	adjacent[b].push_back(a);
	return;
}
