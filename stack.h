//============================================================================
// Name        : stack.h
//
// Desc		   : stack h file, defining stack class
//
// Author      : Mason Groesbeck
//============================================================================

#include <iostream>
#ifndef STACK
#define STACK



class Stack {
	private:
	struct Node {
		int value;
		Node* next;
	};

	Node* head;


	public:
	Stack();
	Stack(Stack const &other);
	void operator=(Stack const &other);
	void push(int value);
	int  pop();
	bool is_empty();


	~Stack();


};

#endif // STACK
