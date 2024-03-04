#pragma once
#include "Event.h"
#include"Passengers.h"
#include <iostream>
using namespace std;


// Declaration of the ArrivalEvent class, derived from the Event class
class ArrivalEvent : public Event {
    // Private member variables
    string passengertype;  // Type of passenger (NP, WP, SP)
    string SpType;         // Special passenger type (for SP)
    int Id;                // Passenger ID
    int on_offTime;        // On/Off time of the event
    Passengers* PassengerPtr;  // Pointer to the passenger object
    int endStation;        // End station for the passenger

public:
    // Constructors with different parameter sets
    ArrivalEvent(Time t, string passtype, int id, int startst, int endst, int ootime);
    ArrivalEvent(Time t, string passtype, int id, int startst, int endst, int ootime, string SPType);

    // Check if the special passenger type is empty
    bool isSpTypeEmpty();

    // Execute the arrival event and update the company's state
    virtual void excute(Company* CPtr);

    // Destructor for the ArrivalEvent class
    ~ArrivalEvent();
};
