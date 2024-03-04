#pragma once
template <typename T>
class QueueADT
{
public:
	virtual bool peek(T& item) const = 0;
	virtual bool dequeue(T& item) = 0;
	virtual bool enqueue(const T& item) = 0;
	virtual bool isempty() = 0;

};
