#include "Event.h"


// Getter function to retrieve the time associated with the event
Time Event::GetTime()
{
    return times;
}

// Getter function to retrieve the starting station for the event
int Event::GetCurrentStation()
{
    return startStation;
}
