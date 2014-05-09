#ifndef __EXPRESSIONTOKEN_HJQ__
#include "ExpressionToken.h"
#endif

#ifndef __STACK__HJQ__
#define __STACK__HJQ__

class StackEmptyException {};

class StackNode{
public:
	ExpressionToken op;
	StackNode* n;
	StackNode();
	StackNode(ExpressionToken _op);
private:
};

class Stack {
public:
	Stack();
	void push(ExpressionToken _op);
	ExpressionToken pop() throw(StackEmptyException);
	ExpressionToken peak() throw(StackEmptyException);
	bool isEmpty();
private:
	StackNode* p;
};
#endif