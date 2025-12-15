//============================================================================
// Name        : queue.cpp
//
// Desc		   : queue cpp file
//
// Author      : Mason Groesbeck
//============================================================================

#include <iostream>
#include "queue.h"

// queue default constructor
// pre: N/A
// post: sets members of queue instance
Queue::Queue() {
	head = nullptr;
}

// queue copy constructor
// pre: another instance of queue
// post: creates a new instance of queue copied other
Queue::Queue(Queue const &other) {
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

// queue overload operator
// pre: another instance of queue
// post: sets one instace of queue equal
// to another
void Queue::operator=(Queue const &other) {
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


// adds data to the queue
// pre: an int value
// post: adds the int into the end node of queue
void Queue::enqueue(int value) {
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
// post: removes the last node from queue and
// returns its value
int Queue::dequeue() {
	if (head == nullptr) {
		throw std::runtime_error("ERROR: Queue is empty!!");
	}

	if (head->next == nullptr) {
		int temp = head->value;
		delete head;
		head = nullptr;
		return temp;
	}

	int temp = head->value;
	Node* new_head = head->next;
	delete head;
	head = new_head;
	return temp;
}

// checks if the queue is empty
// pre: N/A
// post: returns a bool
bool Queue::is_empty() {
	if (head == nullptr) {
		return true;
	} else {
		return false;
	}
}

// queue destructor
// pre: N/A
// post: deallocates previosuly
// allocated memory
Queue::~Queue() {
	Node* iter = head;
	while (iter != nullptr) {
		Node* next = iter->next;
		delete iter;
		iter = next;
	}
}
