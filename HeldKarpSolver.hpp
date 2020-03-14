#ifndef HELDKARPSOLVER_HPP
#define HELDKARPSOLVER_HPP

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

#include "edgeMethods.hpp"

class HeldKarpSolver {
public:
	HeldKarpSolver();
	HeldKarpSolver(int size);
	~HeldKarpSolver();
	int* solve(int** E);
	int* solve(int** E, int size);
	int findWeight(int** E);

	int* order;
	std::vector<std::vector<int>> bests;
	std::vector<std::vector<int>> last;
	int size;
};

#endif
