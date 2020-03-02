#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>

#include "Node.hpp"

// constant for ease of changing input and output
char * inFile = "graph.txt";


// modified read function that assumes the first
// 'word' is an integer, and returns the integer.
// assumes the number to read is <10^6
// copied from shopping program submitted earlier this term
int readInt(FILE * rf) {
	// initialize the temporary array for reading into
	int cap = 7;
	char * buff = (char *)malloc(sizeof(char) * cap);
	char c = fgetc(rf);
	int i = 0;
	// read until reaching an endline, EOF, space, or the buffer is full
	while (c != 10 && c > 0 && i < cap - 1 && c != 32) {
		buff[i] = c;
		i++;
		c = fgetc(rf);
	}
	buff[i] = 0;
	// return the integer that the string represents
	// will end up as -1 if the file was empty
	int out = atoi(buff);
	free(buff);
	return out;
}


// function to read each vertex in from the file
// outputs the pointer to the vertex array
Node* readInPoints(FILE * fIn, int size){
	int i;
	Node * out = new Node[size];
	for (i = 0; i < size; i++) {
		out[i].x = readInt(fIn);
		out[i].y = readInt(fIn);
	}
	return out;
}


// finds the distance between two nodes
int distance(Node n1, Node n2) {
	int xPortion = n1.x - n2.x;
	int yPortion = n1.y - n2.y;
	xPortion = xPortion * xPortion;
	yPortion = yPortion * yPortion;
	int square = xPortion + yPortion;
	double dist = sqrt(square);
	return (int)round(dist);
}


// creates the matrix such that E[i][j] is
// the distance between V[i] and V[j]
// returns the pointer to the array
int** setUpEdgeMatrix(Node * V, int size) {
	int i, j;

	int ** E = (int**)malloc(sizeof(int*) * (size));
	for (i = 0; i < size; i++) {
		E[i] = (int*)malloc(sizeof(int) * (size));
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			E[i][j] = distance(V[i], V[j]);
		}
	}
	return E;
}


int main() {
	// set up input and output file descriptors
	FILE * inFD, * outFD;
	inFD = fopen(inFile, "r");
	int outFileNameSize = strlen(inFile) + 6;
	char outFile[outFileNameSize];
	strcpy(outFile, inFile);
	strcat(outFile, ".tour");
	outFD = fopen(outFile, "w");

	// set up variables
	int count = readInt(inFD);
	Node * V = readInPoints(inFD, count);
	int** E = setUpEdgeMatrix(V, count);

	// build a TSP cycle


	// write the cycle to a file


	// free all the memory
	for (int i = 0; i < count; i++) {
		free(E[i]);
	}
	free(E);
	delete[] V;
	fclose(inFD);
	fclose(outFD);
}