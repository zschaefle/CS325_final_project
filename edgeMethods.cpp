
#include "edgeMethods.hpp"

int ** setUpEdgeMatrix(Node * V, int size) {
	int i, j;

	int ** E = (int**)malloc(sizeof(int*) * (size));
	for (i = 0; i < size; i++) {
		E[i] = (int*)malloc(sizeof(int) * (size));
	}

	for (i = 0; i < size; i++) {
		for (j = i; j < size; j++) {
			E[i][j] = distance(V[i], V[j]);
		}
	}
	return E;
}

int getEdgeFromE(int ** E, int a, int b) {
	if (a <= b) {
		return E[a][b];
	} else {
		return E[b][a];
	}
}

int distance(Node n1, Node n2) {
	int xPortion = n1.x - n2.x;
	int yPortion = n1.y - n2.y;
	xPortion = xPortion * xPortion;
	yPortion = yPortion * yPortion;
	int square = xPortion + yPortion;
	double dist = sqrt(square);
	return (int)round(dist);
}