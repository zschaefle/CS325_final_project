#include "Christofides.hpp"
#include "edgeMethods.hpp"

Christofides::Christofides(int ** E, Node * V, int count) {
	this->E = E;
	this->V = V;
	this->count = count;
	this->epf = new EPFleury(count);
}

Christofides::~Christofides() {
	delete epf;
}

// function to generate a minimum spanning tree
// uses Prim's algorithm
// copied mostly from the MST homework
void Christofides::genMSTEdges() {
	int * treeArr = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; i++) {
		treeArr[i] = 0;
	}
	// first edge is the smallest possible edge
	int * edge = findSmallestAvailable(treeArr);
	// add the edge to all the things that might need it
	treeArr[edge[0]] = 1;
	treeArr[edge[1]] = 1;
	V[edge[0]].addEdge(V[edge[1]].id);
	V[edge[1]].addEdge(V[edge[0]].id);
	epf->addEdge(edge[0], edge[1]);

	delete[] edge;

	// while there is at least one 0 in the tracking array
	int uc = unconnectedCount(treeArr, count);
	while (uc > 0) {
		// find the smallest edge to a node that connects to the tree
		int * edge = findSmallestConnected(treeArr);
		// add the edge to all the things that might need it
		treeArr[edge[0]] = 1;
		treeArr[edge[1]] = 1;
		V[edge[0]].addEdge(V[edge[1]].id);
		V[edge[1]].addEdge(V[edge[0]].id);
		epf->addEdge(edge[0], edge[1]);
		// print it out
		delete[] edge;
		// grab the next
		uc = unconnectedCount(treeArr, count);
	}
	free(treeArr);
}

// function to generate a perfect matching for odd-degree nodes
void Christofides::perfectMatchMultigraph() {
	int * treeArr = (int*)calloc(count, sizeof(int));
	// mark the odd-degree nodes
	for (int i = 0; i < count; i++) {
		if (V[i].edges.size() % 2 != 0) {
			treeArr[i] = 0;
		} else {
			treeArr[i] = 1;
		}
	}
	// continuously find the smallest edge with no connections
	// to already matched nodes
	int * edge = findSmallestAvailable(treeArr);
	while (edge[0] != -1) {
		treeArr[edge[0]] = 1;
		treeArr[edge[1]] = 1;
		V[edge[0]].addEdge(V[edge[1]].id);
		V[edge[1]].addEdge(V[edge[0]].id);
		epf->addEdge(edge[0], edge[1]);
		delete[] edge;
		edge = findSmallestAvailable(treeArr);
	}
	delete[] edge;
	free(treeArr);
}

// converts a eulerian path to a hamiltonian path
// does so by traversing the given path, and adding new vertices to 
// the hamiltonian path.
int * Christofides::makeHamFromEul(std::vector<int>* Euler) {
	int outIdx = 0;
	int * output = (int*)malloc(count * sizeof(int));
	bool * used = new bool[count];
	std::memset(used, false, count);
	for (int euIdx = 0; euIdx < Euler->size(); euIdx++) {
		int next = Euler->at(euIdx);
		if (!(used[next])) {
			output[outIdx] = next;
			outIdx++;
			used[next] = true;
		}
	}
	delete[] used;
	return output;
}

// function that combines all the necessary function calls
int * Christofides::makeChristofidesTour() {
	genMSTEdges();
	perfectMatchMultigraph();
	epf->buildPath();
	std::vector<int> * eCircuit = epf->getPath();
	int * hamPath = makeHamFromEul(eCircuit);
	return hamPath;
}

// below is all from the mst algorithm from HW 4

// finds the smallest available edge
int* Christofides::findSmallestAvailable(int* treeArr) {
	int * output = new int[2];
	output[0] = -1; output[1] = -1;
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if ((output[0] != i || output[1] != j)
				&& (treeArr[i] == 0 && treeArr[j] == 0)) {
				if (output[0] == -1) {
					output[0] = i;
					output[1] = j;
				} else if (getEdgeFromE(E, output[0], output[1]) > getEdgeFromE(E, i, j)) {
					output[0] = i;
					output[1] = j;
				}
			}
		}
	}
	return output;
}


// finds the smallest edge such that
// one vertex  in the edge is part of
// the connected set and one vertex is not.
int* Christofides::findSmallestConnected(int* treeArr) {
	int * output = new int[2];
	output[0] = -1; output[1] = -1;
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if ((output[0] != i || output[1] != j) && treeArr[i] != treeArr[j]) {
				if (output[0] == -1) {
					output[0] = i;
					output[1] = j;
				} else if (getEdgeFromE(E, output[0], output[1]) > getEdgeFromE(E, i, j)) {
					output[0] = i;
					output[1] = j;
				}
			}
		}
	}
	return output;
}


// finds the count of unconnected vertices
int Christofides::unconnectedCount(int * array, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] == 0) count++;
	}
	return count;
}