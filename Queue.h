#ifndef __QUEUE_HJQ__
#define __QUEUE_HJQ__

template<class T>
class QueueNode {
public:
	T v;
	QueueNode* n;
	QueueNode* p;
	QueueNode();
	QueueNode(T _token);
private:
};

template<class T>
class Queue {
public:
	Queue();
	QueueNode<T> *h;
	void insertToTail(T _token);
	void insertToHead(T _token);
	T quitFromHead();
private:
	QueueNode<T> *t;
};









template<class T>
QueueNode<T>::QueueNode(){}

template<class T>
QueueNode<T>::QueueNode(T _token)
{
	v=_token;
	n=NULL;
	p=NULL;
}

template<class T>
Queue<T>::Queue() {
	t=h=NULL;
}

template<class T>
void Queue<T>::insertToTail(T _token) {
	if(h==NULL) {
		h=new QueueNode<T>(_token);
		t=h;
	}else{
		t->n=new QueueNode<T>(_token);
		t->n->p=t;
		t=t->n;
	}
}

template<class T>
void Queue<T>::insertToHead(T _token) {
	if(h==NULL) {
		h=new QueueNode<T>(_token);
		t=h;
	}else{
		QueueNode<T>* newh=new QueueNode<T>(_token);
		newh->n=h;
		h->p=newh;
		h=newh;
	}
}

template<class T>
T Queue<T>::quitFromHead() {
	QueueNode<T> res = *h;
	QueueNode<T> *tmp = h;
	h=h->n;
	delete tmp;
	return res.v;
}

#endif