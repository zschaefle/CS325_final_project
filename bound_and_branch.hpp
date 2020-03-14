#ifndef BOUND_AND_BRANCH_HPP
#define BOUND_AND_BRANCH_HPP

#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>
#include "edgeMethods.hpp"


class BNB_solver{
public:
	BNB_solver(int n);
	~BNB_solver();

	int *final_path;
	int count;
	bool *visited;

	int final_res;

	void TSP(int **E);
	void copyToFinal(int *curr_path);
	int firstMin(int **E, int k);
	int secondMin(int **E, int i);
	void TSPRec(int **E, int curr_bound, int curr_weight, 
	            int level, int *curr_path) ;

};

#endif 
