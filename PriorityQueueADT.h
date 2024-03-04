#pragma once

template<typename T>
class PriorityQueueADT {
public:
    virtual bool isEmpty() const = 0;
    virtual bool enQueue(T item, int prio) = 0;
    virtual bool deQueue(T& item) = 0;
    virtual bool peek(T& item) const = 0;
    virtual ~PriorityQueueADT() {}
};