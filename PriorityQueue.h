#pragma once
#include"PQNode.h"
#include"PriorityQueueADT.h"
template<typename T>
class PriorityQueue : public PriorityQueueADT<T> {
private:
	PQNode<T>* front;
	PQNode<T>* rear;
	int count;
public:
	PriorityQueue() {
		front = nullptr;
		rear = nullptr;
		count = 0;
	}
	bool isEmpty() const override{
		return(front == nullptr);
	}
	bool enQueue(T item, int prio) override
	{
		PQNode<T>* temp = new PQNode<T>(item, prio);
		if (isEmpty()) {
			front = temp;
			rear = temp;
			count++;
			return true;
		}
		if (front->getPrio() >= temp->getPrio()) {
			temp->setNext(front);
			front = temp;
			count++;
			return true;
		}
		PQNode<T>* current = front;
		while (current->getNext()) {
			if (current->getNext()->getPrio() >= temp->getPrio()) {
				temp->setNext(current->getNext());
				current->setNext(temp);
				count++;
				return true;
			}
			current = current->getNext();
		}
		current->setNext(temp);
		rear = temp;
		rear->setNext(nullptr);
		count++;
		return true;

	}
	bool deQueue(T& item) override {
		if (isEmpty())
			return false;

		PQNode<T>* nodeToDeletePtr = front;
		item = front->getItem();
		front = front->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == rear)	 // Special case: last node in the queue
			rear = nullptr;
		delete nodeToDeletePtr;
		count--;
		return true;
	}
	bool peek(T& item) const override{
		if (front) {
			item = front->getItem();
			return true;
		}
		return false;
	}
	~PriorityQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (deQueue(temp));
	}
	PriorityQueue(const PriorityQueue<T>& LQ) //COPY CONSTRUCTOR
	{
		{
			PQNode<T>* NodePtr = LQ.front;
			count = LQ.count;
			if (!NodePtr) //LQ is empty
			{
				front = rear = nullptr;
				return;
			}

			//insert the first node
			PQNode<T>* ptr = new PQNode<T>(NodePtr->getItem(), NodePtr->getPrio());
			front = rear = ptr;
			NodePtr = NodePtr->getNext();

			//insert remaining nodes
			while (NodePtr)
			{
				PQNode<T>* ptr = new PQNode<T>(NodePtr->getItem(), NodePtr->getPrio());
				rear->setNext(ptr);
				rear = ptr;
				NodePtr = NodePtr->getNext();
			}
		}
	}

	int getCount()
	{
		return count;
	}

	PriorityQueue<T> getCopy() {
		PriorityQueue<T> copyQueue;
		PQNode<T>* current = front;
		while (current) {
			copyQueue.enQueue(current->getItem(), current->getPrio());
			current = current->getNext();
		}
		return copyQueue;
	}

};
