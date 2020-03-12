#include "TwoOpt.hpp"


//outline via: https://www.technical-recipes.com/2012/applying-c-implementations-of-2-opt-to-travelling-salesman-problems/
void TwoOpt(int ** E, int * tour, int size) {
	int improve = 0;
	int trial_route[size];
	while (improve < 3) {
		int dist = calcDist(E, tour, size);
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				int counter = 0;
				for (int k = 0; k <= i - 1; k++) {
					trial_route[counter] = tour[k];
					counter++;
					// printf("counter a: %d\n", counter);
				}
				for (int k = j; k >= i; k--) {
					trial_route[counter] = tour[k];
					counter++;
					// printf("counter b: %d\n", counter);
				}
				for (int k = j + 1; k < size; k++) {
					trial_route[counter] = tour[k];
					counter++;
					// printf("counter c: %d\n", counter);
				}
				int newDist = calcDist(E, trial_route, size);
				// printf("old dist: %d\nnew dist: %d\n", dist, newDist);
				if (dist > newDist) {
					for (int k = 0; k < size; k++) {
						tour[k] = trial_route[k];
						// printf("tour[%d] = %d\n", k, tour[k]);
					}
					improve = 0;
					dist = newDist;
				}
			}
		}
		improve++;
	}
}

int calcDist(int** E, int * tour, int size) {
	int output = 0;
	int i;
	for (i = 0; i < size - 1; i++) {
		output += E[tour[i]][tour[i+1]];
	}
	output += E[tour[i]][tour[0]];
	return output;
}
