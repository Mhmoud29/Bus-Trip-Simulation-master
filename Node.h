#pragma once

template<typename T>
class Node
{
private:
	T item;
	Node<T>* next;
public:
	Node();
	Node(T newItem);
	void setItem(T newItem);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
};


template<typename T>
Node<T>::Node() {
	this->item = T();
}

template<typename T>
Node<T>::Node(T newItem) {
	this->item = newItem;
}

template<typename T>
void Node<T>::setItem(T newItem) {
	this->item = newItem;
}

template<typename T>
void Node<T>::setNext(Node<T>* nextNodePtr) {
	this->next = nextNodePtr;
}

template<typename T>
T Node<T>::getItem() const {
	return this->item;
}

template<typename T>
Node<T>* Node<T>::getNext() const {
	return this->next;
}