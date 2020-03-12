#include "HeldKarpSolver.hpp"

HeldKarpSolver::HeldKarpSolver() {
	this->order = NULL;
	size = 0;
}

HeldKarpSolver::HeldKarpSolver(int size) {
	this->order = new int[size];
	this->size = size;
}

HeldKarpSolver::~HeldKarpSolver() {
	if (this->order != NULL) {
		delete[] this->order;
	}
}

// found a guide on how implement H-K at
// https://www.quora.com/Are-there-any-good-examples-of-the-Held-Karp-algorithm-in-C++-Hard-to-find-example-code-to-solve-the-traveling-salesman-problem-Everyone-wants-to-just-talk-about-theory-and-not-show-how-to-actually-do-it-What-is-the-big-secret
// credit: Michal Forisek
// does not include instructions on figuring the optimal path
int * HeldKarpSolver::solve(int ** E) {
	std::vector< std::vector<int> > best( 1<<(this->size-1), std::vector<int>( this->size, INT_MAX ) );
	 
	// use DP to solve all states
	// note that whenever we solve a particular state, 
	// the smaller states we need have already been solved

	for (int visited = 1; visited < (1<<(this->size-1)); ++visited) {
	    for (int last = 0; last < (this->size-1); ++last) {
	 
	        // last visited vertex must be one of the visited vertices
	        if (!(visited & 1<<last)) continue;
	 
	        // try all possibilities for the previous vertex,
	        // pick the best among them
	        if (visited == 1 << last) {
	            // previous vertex must have been N-1
	            best[visited][last] = E[this->size-1][last];
	        } else {
	            // previous vertex was one of the other ones in "visited"
	            int prev_visited = visited ^ 1<<last;
	            for (int prev = 0; prev < this->size-1; ++prev) {
	                if (!(prev_visited & 1<<prev)) continue;
	                best[visited][last] = std::min( 
	                    best[visited][last], 
	                    E[last][prev] + best[prev_visited][prev]
	                );
	            }
	        }
	        printf("best[%d][%d] = %d\n", visited, last);
	    }
	}
}

int * HeldKarpSolver::solve(int ** E, int size) {
	if (this->order != NULL) {
		delete[] this->order;
	}
	this->order = new int[size];
	this->size = size;
	return solve(E);
}

int HeldKarpSolver::findWeight(int ** E) {
	int answer = E[0][this->size-1] + bests[(1<<(this->size-1))-1][0];
	for(int tail = 1; tail < this->size-1; tail++) {
		answer =
			std::min(answer, E[tail][this->size-1] + (bests[(1<<(this->size-1))-1][tail]));
	}
	return answer;
}
