//============================================================================
// Name        : queue.h
//
// Desc		   : queue h file, defining queue class
//
// Author      : Mason Groesbeck
//============================================================================

#ifndef QUEUE
#define QUEUE
#include <iostream>

class Queue {
	private:
	struct Node {
		int value;
		Node* next;
	};

	Node* head;

	public:
	Queue();
	Queue(Queue const &other);

	void operator=(Queue const &other);
	void enqueue(int value);

	int dequeue();

	bool is_empty();

	~Queue();
};

#endif // QUEUE
