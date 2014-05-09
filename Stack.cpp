#include "stdafx.h"
#ifndef __STACK__HJQ__
#include "Stack.h"
#endif


StackNode::StackNode(){}

StackNode::StackNode(ExpressionToken _op) {
	op=_op;
}

Stack::Stack(){
	p=NULL;
}

void Stack::push(ExpressionToken _op) {
	if(p==NULL) {
		p=new StackNode(_op);
		p->n=NULL;
	}else{
		StackNode* tmp=new StackNode(_op);
		tmp->n=p;
		p=tmp;
	}
}

ExpressionToken Stack::peak() throw(StackEmptyException) {
	if(p!=NULL) {
		return p->op;
	}
	throw StackEmptyException();
}

ExpressionToken Stack::pop() throw(StackEmptyException) {
	if(p!=NULL) {
		StackNode* tmp= p->n;
		ExpressionToken res=p->op;
		delete p;
		p=tmp;
		return res;
	}
	throw StackEmptyException();
}

bool Stack::isEmpty() {
	return p==NULL;
}