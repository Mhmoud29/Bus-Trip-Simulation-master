#pragma once
#include "Event.h"


class LeaveEvent : public Event
{
public:
    // Constructor with parameters for time, passenger ID, and starting station
    LeaveEvent(Time t, int id, int startSt);

    // Execute the leave event and update the company's state
    virtual void excute(Company* CPtr);
};