#pragma once
#include"Node.h"


template<typename T>
class List
{
private:
	Node<T>* Head;
public:
	//Functions Declration
	List();

	~List();
	void InsertBeg(const T& data);

	Node<T>* getHead() const;

	void DeleteAll();


	void InsertEnd(const T& data);

	bool Find(T Key);

	int CountOccurance(const T& value);

	void DeleteFirst();

	void DeleteLast();

	bool DeleteNode(const T& value);

	bool DeleteNodes(const T& value);

	void Merge(const List& L);

	void Reverse();
	int getCount();

};

//functions definition
template<typename T>
List<T>::List() {
	Head = nullptr;
}

template<typename T>
List<T>::~List() {
	DeleteAll();
}



template<typename T>
void List<T>::InsertBeg(const T& data) {
	Node<T>* R = new Node<T>(data);
	R->setNext(Head);
	Head = R;
}

template<typename T>
void List<T>::DeleteAll() {
	Node<T>* P = Head;
	while (Head)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
}

template<typename T>
void List<T>::InsertEnd(const T& data) {
	Node<T>* nptr = new Node<T>(data);
	Node<T>* temp = Head;
	if (Head == nullptr) {
		Head = nptr;
	}
	else {
		while (true) {
			if (temp->getNext() == nullptr) {
				temp->setNext(nptr);
				nptr->setNext(nullptr);
				break;
			}
			temp = temp->getNext();
		}
	}
	temp = nullptr;
	nptr = nullptr;
}

template<typename T>
bool List<T>::Find(T Key) {
	Node<T>* temp = Head;
	if (Head == nullptr) {
		temp = nullptr;
		return false;
	}
	bool flag = false;
	while (temp != nullptr) {
		if (temp->getItem() == Key) {
			flag = true;
		}
		temp = temp->getNext();
	}
	temp = nullptr;
	return flag;
}

template<typename T>
int List<T>::CountOccurance(const T& value) {
	Node<T>* temp = Head;
	int count = 0;
	if (Head == nullptr) {
		temp = nullptr;
		return 0;
	}
	while (temp != nullptr) {
		if (temp->getItem() == value) {
			count++;
		}
		temp = temp->getNext();
	}
	return count;
}

template<typename T>
void List<T>::DeleteFirst() {
	if (Head == nullptr) {
		return;  // Return without doing anything if the list is empty
	}

	Node<T>* temp = Head;
	Head = temp->getNext();
	delete temp;
	temp = nullptr;
}

template<typename T>
void List<T>::DeleteLast() {
	if (Head == nullptr) {
		return;  // Return without doing anything if the list is empty
	}

	Node<T>* temp = Head;
	Node<T>* previous = nullptr;

	while (temp->getNext() != nullptr) {
		previous = temp;
		temp = temp->getNext();
	}

	if (previous != nullptr) {
		// There's more than one node in the list
		previous->setNext(nullptr);
	}
	else {
		// There's only one node in the list
		Head = nullptr;
	}

	delete temp;
	temp = nullptr;
}

template<typename T>
bool List<T>::DeleteNode(const T& value) {
	if (Head == nullptr) {
		return false;  // Return without doing anything if the list is empty
	}
	Node<T>* temp = Head;
	Node<T>* prev = nullptr;
	if (Head->getItem() == value) {
		Head = temp->getNext();
		delete temp;
		return true;
	}
	while (temp != nullptr) {
		if (temp->getItem() == value) {
			prev->setItem(temp->getNext());
			delete temp;
			return true;
		}
		prev = temp;
		temp = temp->getNext();
	}
	temp = nullptr;
	return false;

}

template<typename T>
bool List<T>::DeleteNodes(const T& value) {
	Node<T>* temp = Head;
	Node<T>* prev = nullptr;
	bool isDeleted = false;
	while (temp) {
		if (Head->getItem() == value) {
			Head = Head->getNext();
			delete temp;
			temp = Head;
			isDeleted = true;
		}
		else if (temp->getItem() == value) {
			prev->setNext(temp->getNext());
			delete temp;
			temp = prev->getNext();
			isDeleted = true;
		}
		else {
			prev = temp;
			temp = temp->getNext();
		}

	}
	return isDeleted;
}

template<typename T>
void List<T>::Merge(const List<T>& L) {
	Node<T>* temp = this->Head;
	while (temp) {
		if (temp->getNext() == nullptr) {
			temp->setNext(L.getHead());
			return;
		}
		temp = temp->getNext();
	}
}

template<typename T>
void List<T>::Reverse() {
	Node<T>* current = Head;
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;

	while (current != nullptr) {
		next = current->getNext();  // Save the next node

		// Reverse the next pointer of the current node
		current->setNext(prev);

		// Move to the next node
		prev = current;
		current = next;
	}

	// Update the head to point to the last node, which is the new head
	Head = prev;
}

template<typename T>
int List<T>::getCount()
{
	if (Head == nullptr) {
		return 0;  // Return without doing anything if the list is empty
	}
	int count = 1;
	Node<T>* temp = Head;
	while (temp) {
		temp = temp->getNext();
		count++;
	}
	return count;
}


template<typename T>
Node<T>* List<T>::getHead() const {
	return Head;
}