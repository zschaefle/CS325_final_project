#ifndef TWOOPT_HPP
#define TWOOPT_HPP

#include <cstdio>
#include "edgeMethods.hpp"

void TwoOpt(int ** E, int * tour, int size);
int calcDist(int ** E, int * tour, int size);

#endif
