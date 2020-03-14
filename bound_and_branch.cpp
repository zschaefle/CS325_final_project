#include "bound_and_branch.hpp"


BNB_solver::BNB_solver(int n){
    this->count = n;
    this->final_path = new int[count];
    this->visited = new bool[count];
    for(int j=0; j<count; j++){
        this->visited[j] = false;
    }

    final_res = INT_MAX;
}

BNB_solver::~BNB_solver(){

    delete [] final_path;

    delete [] visited;

}

void BNB_solver::copyToFinal(int *curr_path) 
{ 
    for (int i=0; i<count; i++) 
        final_path[i] = curr_path[i]; 
    final_path[count] = curr_path[0]; 
} 

int BNB_solver::firstMin(int **E, int k){
	int min = INT_MAX;
	for(int i=0; i<count; i++){
		if(getEdgeFromE(E,k,i)<min && i!=k){
			min = E[k][i];
		}
	}
	return min;
}

int BNB_solver::secondMin(int **E, int i) 
{ 
    int first = INT_MAX, second = INT_MAX; 
    for (int j=0; j<count; j++) 
    { 
        if (i == j) 
            continue; 
  
        if (getEdgeFromE(E,i,j) <= first) 
        { 
            second = first; 
            first = getEdgeFromE(E,i,j); 
        } 
        else if (getEdgeFromE(E,i,j) <= second && getEdgeFromE(E,i,j) != first) 
            second = getEdgeFromE(E,i,j); 
    } 
    return second; 
} 

void BNB_solver::TSPRec(int **E, int curr_bound, int curr_weight, 
            int level, int *curr_path) 
{ 
    // base case is when we have reached level N which 
    // means we have covered all the nodes once 
    if (level==count) 
    { 
        // check if there is an edge from last vertex in 
        // path back to the first vertex 
        if (getEdgeFromE(E,curr_path[level-1],curr_path[0]) != 0) { 
            // curr_res has the total weight of the 
            // solution we got 
            int curr_res = curr_weight + getEdgeFromE(E,curr_path[level-1],curr_path[0]); 
  
            // Update final result and final path if 
            // current result is better. 
            if (curr_res < final_res) 
            { 
                copyToFinal(curr_path); 
               final_res = curr_res; 
            } 
        } 
        return; 
    } 
    for (int i=0; i<count; i++) { 
        // Consider next vertex if it is not same (diagonal 
        // entry in adjacency matrix and not visited 
        // already) 
        if (getEdgeFromE(E, curr_path[level-1],i) != 0 && visited[i] == false) 
        { 
            int temp = curr_bound; 
            curr_weight += getEdgeFromE(E, curr_path[level-1],i); 
  
            // different computation of curr_bound for 
            // level 2 from the other levels 
            if (level==1) 
              curr_bound -= ((firstMin(E, curr_path[level-1]) + firstMin(E, i))/2); 
            else
              curr_bound -= ((secondMin(E, curr_path[level-1]) + firstMin(E, i))/2); 
  
            // curr_bound + curr_weight is the actual lower bound 
            // for the node that we have arrived on 
            // If current lower bound < final_res, we need to explore 
            // the node further 
            if (curr_bound + curr_weight < final_res) { 
                curr_path[level] = i; 
                visited[i] = true; 
  
                // call TSPRec for the next level 
                TSPRec(E, curr_bound, curr_weight, level+1, curr_path); 
            } 
            // Else we have to prune the node by resetting 
            // all changes to curr_weight and curr_bound 
            curr_weight -= getEdgeFromE(E, curr_path[level-1],i); 
            curr_bound = temp; 
  
            // Also reset the visited array 
            memset(visited, false, sizeof(visited)); 
            for (int j=0; j<=level-1; j++) 
                visited[curr_path[j]] = true; 
        } 
    } 
} 

void BNB_solver::TSP(int **E) 
{ 
    
    int *curr_path = new int[this->count+1]; 
  
    // Calculate initial lower bound for the root node 
    // using the formula 1/2 * (sum of first min + 
    // second min) for all edges. 
    // Also initialize the curr_path and visited array 
    int curr_bound = 0; 
    memset(curr_path, -1, sizeof(curr_path)); 
    memset(visited, 0, sizeof(curr_path)); 
  
    // Compute initial bound
    
    for (int i=0; i<count; i++) {
        curr_bound += (firstMin(E, i) + secondMin(E, i)); 
    }
  
    // Rounding off the lower bound to an integer 
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2; 
  
    // We start at vertex 1 so the first vertex 
    // in curr_path[] is 0 
    visited[0] = true; 
    curr_path[0] = 0; 
  	TSPRec(E, curr_bound, 0, 1, curr_path); 
} 