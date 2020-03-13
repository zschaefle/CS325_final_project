#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>

#include "Node.hpp"
#include "TwoOpt.hpp"
#include "bound_and_branch.hpp"

// constant for ease of changing input and output
char * inFile = "tsp_example_1.txt";

// modified read function that assumes the first
// 'word' is an integer, and returns the integer.
// assumes the number to read is <10^6
// copied from shopping program submitted earlier this term
int readInt(FILE * rf) {
	// initialize the temporary array for reading into
	int cap = 10;
	char * buff = (char *)malloc(sizeof(char) * cap);
	char c = fgetc(rf);
	if (c < 0) {
		free(buff);
		return -1;
	}
	int i = 0;
	// clear leading whitespace
	while (c == ' ') {
		c = fgetc(rf);
	}
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

// function to get the number of lines with "useful" data,
// ends after reaching EOF or two consequtive newlines.
// the file pointer will be reset to the beginning of the file.
int fileLineCount(FILE * rf) {
	// initialize the temporary array for reading into
	char c = fgetc(rf);
	int i = 0, lineHasContent = 0;
	while (c > 0) {
		if (c == '\n' || c < 0) {
			if (lineHasContent == 1) {
				i++;
				lineHasContent = 0;
			} else {
				fseek(rf, 0, SEEK_SET);
				return i;
			}
		}
		else {
			lineHasContent = 1;
		}
		c = fgetc(rf);
		// std::cout << c;
	}
	fseek(rf, 0, SEEK_SET);
	return i;
}


// function to read each vertex in from the file
// outputs the pointer to the vertex array
Node* readInPoints(FILE * fIn, int size){
	Node * out = new Node[size];
	for (int i = 0; i < size; i++) {
		out[i].id = readInt(fIn);
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
			// std::cout << "[" << E[i][j] << "] ";
		}
		// std::cout << std::endl;
	}
	return E;
}


void printTourToFile(FILE * fOut, int * indices, int size, int** E) {
	int sum = 0;
	for (int i = 0; i < size - 1; i++) {
		sum += E[indices[i]][indices[i+1]];
	}
	sum += E[indices[0]][indices[size - 1]];
	fprintf(fOut, "%d\n", sum);

	for (int i = 0; i < size; i++) {
		fprintf(fOut, "%d", indices[i]);
		if (i != size - 1) {
			fprintf(fOut, "\n");
		}
	}
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
	int count = fileLineCount(inFD);
	Node * V = readInPoints(inFD, count);
	int** E = setUpEdgeMatrix(V, count);

	// build a TSP cycle

	// int ** test = (int**)malloc(sizeof(int*) * 4);
	// for (int i = 0; i < 4; i++) {
	// 	test[i] = (int*)malloc(sizeof(int) * 4);
	// }
	// test[0][0] = 0; test[0][1] = 1; test[0][2] = 3; test[0][3] = 60;
	// test[1][0] = 1; test[1][1] = 0; test[1][2] = 2; test[1][3] = 3;
	// test[2][0] = 3; test[2][1] = 1; test[2][2] = 0; test[2][3] = 2;
	// test[3][0] = 60; test[3][1] = 3; test[3][2] = 2; test[3][3] = 0;
	// int * testPath = (int*)malloc(4 * sizeof(int));
	// for (int i = 0; i < 4; i++) {
	// 	testPath[i] = i;
	// }


	int * path = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; i++) {
		path[i] = i;
	}


	if (count < 20){
		TwoOpt(E, path, count);
	} else {
		// bound and branch
		BNB_solver bnb(count);
		bnb.TSP(E);
		printTourToFile(outFD, bnb.final_path, count, E);
		
	}



	// write the cycle to a file
	printTourToFile(outFD, path, count, E);

	// free all the memory
	for (int i = 0; i < count; i++) {
		free(E[i]);
	}
	free(E);
	free(path);
	delete[] V;
	fclose(inFD);
	fclose(outFD);
}
