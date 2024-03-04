#ifndef _PQNode
#define _PQNode
#include<iostream>
using namespace std;
//First let's declare a single node in the list
template<typename T>
class PQNode
{
private:
	T item;	// A data item (can be any complex sturcture)
	int priority;
	PQNode<T>* next;	// Pointer to next node
public:

	PQNode() //default constructor
	{
		next = nullptr;
	}

	PQNode(T newItem, int prio) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		priority = prio;

	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(PQNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext
	void setPrio(int prio) {
		priority = prio;
	}

	T getItem() const
	{
		return item;
	} // end getItem

	PQNode<T>* getNext() const
	{
		return next;
	}
	int getPrio()const
	{
		return priority;
	}
}; // end Node

#endif	