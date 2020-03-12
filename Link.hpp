#ifndef LINK_HPP
#define LINK_HPP

#include <stdlib.h>
#include "Node.hpp"

class Link {
public:
	Link();
	Link(Node * item);
	Link(Node * item, Link * next);

	Node * value;
	Link * next;
};

#endif
