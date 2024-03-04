#include "LeaveEvent.h"

// Constructor with parameters for time, passenger ID, and starting station
LeaveEvent::LeaveEvent(Time t, int id, int startSt)
{
    times.setTotalHours(t.getTotalHours());
    times.setTotalMinutes(t.getTotalMinutes());
    ID = id;
    startStation = startSt;
}

// Execute the leave event and update the company's state
void LeaveEvent::excute(Company* CPtr)
{
    // Call the leavePassenger function of the Company class to handle the leave event
    CPtr->leavePassenger(startStation, ID);
}