#include "ArrivalEvent.h"

// Constructor with basic passenger type
ArrivalEvent::ArrivalEvent(Time t, string passtype, int id, int startst, int endst, int ootime)
{
    times.setTotalHours(t.getTotalHours());
    times.setTotalMinutes(t.getTotalMinutes());
    this->passengertype = passtype;
    this->on_offTime = ootime;
    this->Id = id;
    startStation = startst;
    this->endStation = endst;
}

// Constructor with special passenger type
ArrivalEvent::ArrivalEvent(Time t, string passtype, int id, int startst, int endst, int ootime, string SPType)
{
    times.setTotalHours(t.getTotalHours());
    times.setTotalMinutes(t.getTotalMinutes());
    this->passengertype = passtype;
    this->on_offTime = ootime;
    this->Id = id;
    startStation = startst;
    this->endStation = endst;
    this->SpType = SPType;
}

// Check if the special passenger type is empty
bool ArrivalEvent::isSpTypeEmpty() {
    return SpType.empty(); // Check if SpType is an empty string
}

// Execute the arrival event and update the company's state
void ArrivalEvent::excute(Company* CPtr)
{
    // Check if special passenger type is empty
    if (isSpTypeEmpty())
    {
        // Create a new passenger object without special type
        PassengerPtr = new Passengers(passengertype, times, on_offTime, startStation, endStation, Id);

        // Add the passenger to the company's passenger list
        CPtr->addPassenger(PassengerPtr);
    }
    else
    {
        // Create a new passenger object with special type
        PassengerPtr = new Passengers(passengertype, times, on_offTime, startStation, endStation, SpType, Id);

        // Add the passenger to the company's passenger list
        CPtr->addPassenger(PassengerPtr);
    }
}

// Destructor for the ArrivalEvent class
ArrivalEvent::~ArrivalEvent()
{
    delete PassengerPtr; // Delete dynamically allocated PassengerPtr object
}
