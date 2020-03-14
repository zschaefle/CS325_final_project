#ifndef EDGEMETHODS_HPP
#define EDGEMETHODS_HPP

#include "Node.hpp"
#include <cmath>

int ** setUpEdgeMatrix(Node * V, int size);
int getEdgeFromE(int ** E, int a, int b);
int distance(Node n1, Node n2);

#endif