#include "Link.hpp"

// a linked list thing that wasn't actually ever used :/



Link::Link() {
	value = NULL;
	next = NULL;
}

Link::Link(Node * item) {
	value = item;
	next = NULL;
}


Link::Link(Node * item, Link * next) {
	value = item;
	next = next;
}
