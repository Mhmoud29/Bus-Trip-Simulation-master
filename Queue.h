#pragma once
#include "QueueADT.h"
#include "Node.h"
using namespace std;
template <typename T>
class Queue : public QueueADT<T>
{
	Node<T>* head;
	Node<T>* rear;
	int count;
public:
	Queue();
	virtual bool peek(T& item) const;
	virtual bool dequeue(T& item);
	virtual bool enqueue(const T& item);
	virtual bool isempty();
	int GetSize();
	Queue(const Queue<T>& LQ);
	virtual ~Queue();
};

template<typename T>
Queue<T>::Queue()
{
	head = nullptr;
	rear = nullptr;
	count = 0;
}

template<typename T>
bool Queue<T>::peek(T& item) const
{
	if (head == nullptr)
		return false;
	item = head->getItem();
	return true;
}

template<typename T>
bool Queue<T>::dequeue(T& item)
{
	if (isempty())
		return false;
	Node<T>* deletenode = head;
	item = head->getItem();
	head = head->getNext();
	if (!deletenode)
	{
		rear = nullptr;
	}
	delete deletenode;
	count--;
	return true;
}

template<typename T>
bool Queue<T>::enqueue(const T& item)
{
	Node <T>* ptr = new Node<T>(item);
	ptr->setNext(nullptr);
	count++;
	if (!head)
	{
		head = ptr;
		rear = ptr;
		return true;
	}
	rear->setNext(ptr);
	rear = ptr;
	return true;
}
template<typename T>
bool Queue<T>::isempty()
{
	if (head == nullptr)
		return true;
	return false;
}


template<typename T>
int Queue<T>::GetSize()
{
	return count;
}



template<typename T>
Queue<T>::~Queue()
{
	T x;
	while (dequeue(x))
	{
	}
}



template<typename T>

Queue<T>::Queue(const Queue<T>& LQ) //COPY CONSTRUCTOR
{
	{
		Node<T>* NodePtr = LQ.head;
		count = LQ.count;
		if (!NodePtr) //LQ is empty
		{
			head = rear = nullptr;
			return;
		}

		//insert the first node
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		head = rear = ptr;
		NodePtr = NodePtr->getNext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			rear->setNext(ptr);
			rear = ptr;
			NodePtr = NodePtr->getNext();
		}
	}
}


