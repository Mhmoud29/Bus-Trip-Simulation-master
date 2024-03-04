#include "Bus.h"


int Bus::nextBusId = 1;
Bus::Bus(int max_cap, int maintT, int t, int MaxTrips,  BusType type, bool ul,bool l,bool m,int main) : tripsToMaintenance(MaxTrips), bId(nextBusId++) {
    max_capacity = max_cap;
    maintenanceTime = maintT;
    trips = t;
    this->bustype = type;
    this->isUnloading = ul;
    this->isLoading = l;
    this->goingForMaintainance = m;
    this->timeInMaintainance = main;
    this->direction = "FWD";
}


void Bus::setMaxCap(int cap)
{
    this->max_capacity = cap;
}

void Bus::setMaint(int main)
{
    this->maintenanceTime = main;
}

void Bus::setTrips(int trip)
{
    this->trips = trip;
}

void Bus::setCurrentBusTime(Time t)
{
    this->currentBusTime.setTotalHours(t.getTotalHours());
    this->currentBusTime.setTotalMinutes(t.getTotalMinutes());
}

void Bus::setgoingForMaintainance(bool i)
{
    this->goingForMaintainance = i;
}

void Bus::resetTimeInMaintainance()
{
    this->timeInMaintainance = 0;
}

void Bus::setDirection(string d)
{
    this->direction = d;
}

void Bus::setBusMoveTime(Time t)
{
    this->busMoveTime.setTotalHours(t.getTotalHours());
    this->busMoveTime.setTotalMinutes(t.getTotalMinutes());
}

int Bus::getBusID()
{
    return bId;
}

string Bus::getDirection()
{
    return direction;
}

void Bus::increamentTimeInMaintainance()
{
    this->timeInMaintainance += 1;
}


Time Bus::getCurrentBusTime()
{
    return currentBusTime;
}

int Bus::getTimeInMaintainance()
{
    return this->timeInMaintainance;
}

void Bus::load(Passengers* passenger) {
    int busPriority = abs(passenger->getEndStation() - passenger->getStartStation());
    passengerList.enQueue(passenger, busPriority);
}

bool Bus::unload()
{
    //Creating a dummy object from passenger to pass it to the dequeue function
    Passengers* Pass;
    return passengerList.deQueue(Pass);
}

void Bus::setIsUnLoading(bool ul)
{
    this->isUnloading = ul;
}

bool Bus::getIsUnloading()
{
    return this->isUnloading;
}

void Bus::setIsLoading(bool l)
{
    this->isLoading = l;
}

bool Bus::getIsLoading()
{
    return this->isLoading;
}


void Bus::busBusyTime()
{
    this->busyTime.incrementTotalMinutes();
}

Time Bus::getBusBusyTime()
{
    return this->busyTime;
}

Time Bus::calculateTotalBusyTime()
{
    Time T;
    return (busyTime - T);
}

bool Bus::incrementCurrentCap()
{
    if (currentCapacity >= max_capacity) {
        return false;
    }
    currentCapacity++;
    return true;
}

void Bus::decrementCurrentCap()
{
    currentCapacity -= 1;
}

int Bus::getCurrentCap()
{
    return this->currentCapacity;
}



int Bus::getMaxCap() const
{
    return max_capacity;
}

int Bus::getMaint() const
{
    return maintenanceTime;
}

int Bus::getTrips() const
{
    return trips;
}

bool Bus::getgoingForMaintainance() const
{
    return goingForMaintainance;
}

BusType Bus::getBusType() const
{
    return bustype;
}

Time Bus::getBusMoveTime() const
{
    return busMoveTime;
}


void Bus::incrementTrips()
{
    this->trips++;
}

bool Bus::isMaintenanceRequired() const
{
    if (this->trips == tripsToMaintenance) {
        return true;
    }
    return false;
}

void Bus::performMaintenance()
{
    this->trips = 0;
}

void Bus::setNextDestination(int n)
{
    next_destination = n;
}

void Bus::setCurrentDestination(int c)
{
    this->currentStation = c;
}

int Bus::getNextDestination()
{
    return this->next_destination;
}

int Bus::getCurrentDestination()
{
    return this->currentStation;
}

PriorityQueue<Passengers*>& Bus::getpassengerList()
{
    return this->passengerList;
}

ostream& operator<<(ostream& out, const Bus& bus)
{
    out <<bus.bId;
    return out;
}
