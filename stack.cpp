//============================================================================
// Name        : stack.cpp
//
// Desc		   : defines stack class methods
//
// Author      : Mason Groesbeck
//============================================================================

#include <iostream>
#include "stack.h"

// stack default constructor
// pre: N/A
// post: sets members of stack instance
Stack::Stack() {
	head = nullptr;
}

// stack copy constructor
// pre: another instance of stack
// post: creates a new instance of stack copied other
Stack::Stack(Stack const &other) {
	if (other.head == nullptr) {
		 head = nullptr;
		 return;
	}
	head = new Node;
	head->value = other.head->value;
	head->next = nullptr;

	Node* curr = head;
	Node* curr_other = other.head->next;

	while (curr_other != nullptr) {
		curr->next = new Node;
		curr = curr->next;

		curr->value = curr_other->value;
		curr->next = nullptr;

		curr_other = curr_other->next;
	}
}

// stack overload operator
// pre: another instance of stack
// post: sets one instace of stack equal
// to another
void Stack::operator=(Stack const &other) {
	if (this == &other) {
		return;
	}

	Node* iter = head;
	while (iter != nullptr) {
		Node* temp = iter->next;
		delete iter;
		iter = temp;
	}

	head = nullptr;
	Node* curr = nullptr;

	if (other.head == nullptr) {
		return;
	}

	head = new Node;
	head->value = other.head->value;
	head->next = nullptr;

	iter = other.head->next;
	curr = head;
	while (iter != nullptr) {
		curr->next = new Node;
		curr = curr->next;

		curr->value = iter->value;
		curr->next = nullptr;

		iter = iter->next;

	}
}

// adds data to the stack
// pre: an int value
// post: adds the int into the end node of stack
void Stack::push(int value) {
	Node* temp = new Node;
	temp->value = value;
	temp->next = nullptr;

	if (head == nullptr) {
		head = temp;

	} else {
		Node* iter = head;
		while (iter->next != nullptr) {
			iter = iter->next;
		}
		iter->next = temp;
	}
}

// removes the last node and returns its value
// pre: N/A
// post: removes the last node from stack and
// returns its value
int  Stack::pop() {
	if (head == nullptr) {
		throw std::runtime_error("ERROR: Stack is empty!!");
	}

	if (head->next == nullptr) {
		int temp = head->value;
		delete head;
		head = nullptr;
		return temp;
	}

	Node* previous = head;
	Node* iter = head->next;

	while (iter->next != nullptr) {
		previous = iter;
		iter = iter->next;

	}
	int temp = iter->value;
	delete iter;
	previous->next = nullptr;
	return temp;
}

// checks if the stack is empty
// pre: N/A
// post: returns a bool
bool Stack::is_empty() {
	if (head == nullptr) {
		return true;
	} else {
		return false;
	}
}

// stack destructor
// pre: N/A
// post: deallocates previosuly
// allocated memory
Stack::~Stack() {
	Node* iter = head;
	while (iter != nullptr) {
		Node* next = iter->next;
		delete iter;
		iter = next;
	}
}
