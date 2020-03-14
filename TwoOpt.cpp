#include "TwoOpt.hpp"


//outline via: https://www.technical-recipes.com/2012/applying-c-implementations-of-2-opt-to-travelling-salesman-problems/


// function to perform the 2-opt on a given tour
void TwoOpt(int ** E, int * tour, int size) {
	int improve = 0;
	int trial_route[size];
	while (improve < 3) { // while things haven't gotten better...
		int dist = calcDist(E, tour, size);
		for (int i = 0; i < size - 1; i++) { // for each node i
			for (int j = i + 1; j < size; j++) { // for each node j > i
				int counter = 0;
				// create a trial route TR = []
				for (int k = 0; k <= i - 1; k++) {  // TR <= best[0..i-1]
					trial_route[counter] = tour[k];
					counter++;
				}
				for (int k = j; k >= i; k--) { // TR <=(reverse)= best[i..k]
					trial_route[counter] = tour[k];
					counter++;
				}
				for (int k = j + 1; k < size; k++) { // TR <= best[k+1..n]
					trial_route[counter] = tour[k];
					counter++;
				}
				// if the new cycle is better, start using it as the best
				int newDist = calcDist(E, trial_route, size);
				if (dist > newDist) {
					for (int k = 0; k < size; k++) {
						tour[k] = trial_route[k];
					}
					improve = 0;
					dist = newDist;
				}
			}
		}
		improve++;
	}
}

// function to calculate the overall distance of a cycle
int calcDist(int** E, int * tour, int size) {
	int output = 0;
	int i;
	for (i = 0; i < size - 1; i++) {
		output += getEdgeFromE(E, tour[i], tour[i+1]);
	}
	output += getEdgeFromE(E, tour[i], tour[0]);
	return output;
}
