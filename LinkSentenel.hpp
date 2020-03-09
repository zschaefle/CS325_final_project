#ifndef LINKSENTENEL_HPP
#define LINKSENTENEL_HPP

#include <stdlib.h>
#include "Link.hpp"

class LinkSentenel {
public:
	LinkSentenel();

	Link * getFirst();
	Link * getLast();
	void insertFront(Node * in);
	void append(Node * in);
	Node * removeByIdx(int idx);
	Node * removeByValue(Node * value);
	int getSize();
	Link * get(int idx);
private:
	Link * first;
	Link * last;
	int size;
};

#endif
