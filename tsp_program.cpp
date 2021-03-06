#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

#include "Node.hpp"
#include "TwoOpt.hpp"
#include "Christofides.hpp"
#include "edgeMethods.hpp"
#include "bound_and_branch.hpp"

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
		out[i].edges;
	}
	return out;
}

// function to print the given tour to a file
// does no double-checking
// calculates the cost by itself
void printTourToFile(FILE * fOut, int * indices, int size, int** E) {
	int sum = 0;
	// 
	for (int i = 0; i < size - 1; i++) {
		sum += getEdgeFromE(E, indices[i], indices[i + 1]);
	}
	sum += getEdgeFromE(E, indices[0], indices[size - 1]);
	fprintf(fOut, "%d\n", sum);

	for (int i = 0; i < size; i++) {
		fprintf(fOut, "%d", indices[i]);
		if (i != size - 1) {
			fprintf(fOut, "\n");
		}
	}
}


int main(int argc, char * argv[]) {
	// set up input and output file descriptors
	FILE * inFD, * outFD;
	char * inFile = new char[FILENAME_MAX];
	// setup the infile variable based on if one is given or not
	if (argc == 1) {
		// constant for ease of changing input and output
		std::strcpy(inFile, "tsp_example_1.txt");
	} else {
		std::strcpy(inFile, argv[1]);
	}
	inFD = fopen(inFile, "r");
	if (inFD <= 0) { // handle bad input
		std::cerr << inFile << " could not be opened.";
		delete[] inFile;
		return 1;
	}
	// set up the rest of the variables
	int outFileNameSize = strlen(inFile) + 6;
	char outFile[outFileNameSize];
	strcpy(outFile, inFile);
	strcat(outFile, ".tour");
	outFD = fopen(outFile, "w");

	struct timespec tsStart;
	struct timespec tsEnd;

	// record the start
	clock_gettime(CLOCK_REALTIME, &tsStart);

	// set up variables
	int count = fileLineCount(inFD);
	Node * V = readInPoints(inFD, count);
	printf("Starting building the edges...\n");
	int** E = setUpEdgeMatrix(V, count);
	printf("Done with building the edges...\n");
	// build a TSP cycle
	int * path;
	bool bnbIsWorking = false; // for if/when we get Brand-and-Bound working
	// statements deciding what solver to use
	if (count < 1500) {
		if (bnbIsWorking) {
			printf("Using Branch And Bound...\n");
			BNB_solver bnb(count);
			bnb.TSP(E);
			path = bnb.final_path;
		} else {
			printf("Using 2-Opt...\n");
			path = (int*)malloc(count * sizeof(int));
			for (int i = 0; i < count; i++) {
				path[i] = i;
			}
			TwoOpt(E, path, count);
		}
	} else {
		printf("Using Christofides...\n");
		Christofides c(E, V, count);
		path = c.makeChristofidesTour();
	}

	// record the end time
	clock_gettime(CLOCK_REALTIME, &tsEnd);
	// print the time it tood to do the TSP
	printf("Took %f seconds to find the TSP solution for %s\n", (tsEnd.tv_sec - tsStart.tv_sec) + ((double)(tsEnd.tv_nsec - tsStart.tv_nsec) / 1000000000.0), inFile);


	// write the cycle to a file
	printTourToFile(outFD, path, count, E);

	// free all the memory
	for (int i = 0; i < count; i++) {
		free(E[i]);
	}
	free(E);
	free(path);
	delete[] inFile;
	delete[] V;
	fclose(inFD);
	fclose(outFD);
}
