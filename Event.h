#pragma once
#include "Time.h"
#include"Company.h"

class Event
{
protected:
    int ID;             // Unique identifier for the event
    Time times;         // Time associated with the event
    int startStation;   // Starting station for the event

public:
    // Pure virtual function to execute the event and update the company's state
    virtual void excute(Company* CPtr) = 0;

    // Getter function to retrieve the time associated with the event
    Time GetTime();

    // Getter function to retrieve the starting station for the event
    int GetCurrentStation();
};
