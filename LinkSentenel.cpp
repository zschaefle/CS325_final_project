#include "LinkSentenel.hpp"

LinkSentenel::LinkSentenel() {
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}

// gets the first link
Link * LinkSentenel::getFirst() {
	return this->first;
}

// gets the last link
Link * LinkSentenel::getLast() {
	return this->last;
}

// inserts a new link at index 0 and shifts others back by one
void LinkSentenel::insertFront(Node * in) {
	Link * temp = new Link(in, this->first);
	this->first = temp;
	this->size++;
}

// inserts a new link at the end of the list
void LinkSentenel::append(Node * in) {
	Link * temp = new Link(in);
	this->last->next = temp;
	this->last = temp;
	this->size++;
}

// removes a link at a given position and returns the link's value (i.e. it's Node)
Node * LinkSentenel::removeByIdx(int idx) {
	if(idx < 0 || idx >= this->size) {
		return NULL;
	}

	Link * temp = this->first;
	Link * temp2 = this->first;
	for (int i = 0; i < idx; i++) {
		temp2 = temp;
		temp = temp->next;
	}

	Node * value = temp->value;
	temp2->next = temp->next;
	delete temp;
	this->size--;
	return value;
}

// removes a link with a give Node as it's value
// requires the pointer to the node to be removed
Node * LinkSentenel::removeByValue(Node * value) {
	Link * temp = this->first;
	if (temp->value == value) {
		Node * out = temp->value;
		this->first = this->first->next;
		this->size--;
		delete temp;
		return out;
	}

	Link * temp2 = this->first;
	for (int i = 0; i < this->size; i++) {
		if (temp->value == value) {
			break;
		}
		temp2 = temp;
		temp = temp->next;
	}
	Node * out = temp->value;
	temp2->next = temp->next;
	delete temp;
	this->size--;
	return out;
}

// gets the size/length/# of elements in the list
int LinkSentenel::getSize() {
	return this->size;
}

// gets a link at a specified index
Link * LinkSentenel::get(int idx) {
	if (idx >= this->size || idx < 0) {
		return NULL;
	}
	if (idx == this->size - 1) {
		return this->last;
	}
	Link * current = this->first;
	for (int i = 0; i < idx; i++){
		current = current->next;
	}
	return current;
}