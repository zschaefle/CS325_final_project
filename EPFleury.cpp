
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

void EPFleury::removeEdge(int a, int b) {
	std::list<int>::iterator i = std::find(adjacent[a].begin(), adjacent[a].end(), b);
	*i = -1;
	i = std::find(adjacent[b].begin(), adjacent[b].end(), a);
	*i = -1;
}

int EPFleury::DFSCount(int vertex, bool visited[]) {
	visited[vertex] = true;
	int count = 1;

	std::list<int>::iterator i;
	for (i = adjacent[vertex].begin(); i != adjacent[vertex].end(); i++) {
		if (*i != -1 && !(visited[*i])) {
			count += DFSCount(*i, visited);
		}
	}
	return count;
}

bool EPFleury::isValidEdge(int a, int b) {
	int countA = 0;
	std::list<int>::iterator i;
	for (i = adjacent[a].begin(); i != adjacent[a].end(); i++) {
		if (*i != -1) {
			countA++;
		}
	}
	if (countA == 1) {
		return true;
	}


	bool visited[count];
	std::memset(visited, false, count);
	countA = DFSCount(a, visited);

	removeEdge(a, b);
	std::memset(visited, false, count);
	int countB = DFSCount(a, visited);

	addEdge(a, b);

	return (countA > countB) ? false : true;
}

void EPFleury::printAdjacent() {
	std::list<int>::iterator i;
	for (int k = 0; k < count; k++) {
		for (i = adjacent[k].begin(); i != adjacent[k].end(); i++){
			std::cout << "k: " << k << "\telement: " << *i << std::endl;
		}
	}
}

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

std::vector<int> *EPFleury::getPath() {
	if (path->size() < count) {
		// std::cout << "need to build before returning path. size = " << path->size() << " count = " << count << std::cout;
		path->resize(0);
		buildPath();
	}
	// std::cout << "size = " << path->size() << "\tcount = " << count << std::endl;
	std::vector<int>::iterator i;
	for (i = path->begin(); i != path->end(); i++) {
		// std::cout << *i << std::endl;
	}
	return path;
}

void EPFleury::_build(int current) {
	// std::cout << "now at " << current << std::endl;
	std::list<int>::iterator i;
	for (i = adjacent[current].begin(); i != adjacent[current].end(); i++) {
		int vertex = *i;

		if (vertex != -1 && isValidEdge(current, vertex)) {
			removeEdge(current, vertex);
			path->push_back(vertex);
			// std::cout << "travelling to " << vertex << std::endl;
			_build(vertex);
		}
	}
}

void EPFleury::addEdge(int a, int b){
	adjacent[a].push_back(b);
	adjacent[b].push_back(a);
	return;
}
