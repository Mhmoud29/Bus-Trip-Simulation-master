#include "Passengers.h"





Passengers::Passengers()
{
    // Initialize with default values
    SPType = "";
    type = "";
    this->ID = 0;
    On_OffTime = 0;
    startStation = 0;
    endStation = 0;
    priority = 0;
}

Passengers::Passengers(string s, Time& aTime, int ooTime, int startStat, int endStat,int id)
{
    setType(s);
    setArrivalTime(aTime);
    this->ID = id;

    setOn_OffTime(ooTime);
    setStartStation(startStat);
    setEndStation(endStat);
    calculatePriority();
}

Passengers::Passengers(string t, Time& aTime, int ooTime, int startStat, int endStat, string spType,int id)
{
    SPType = spType;
    setType(t);
    setArrivalTime(aTime);
    this->ID = id;
    setOn_OffTime(ooTime);
    setStartStation(startStat);
    setEndStation(endStat);
    calculatePriority(); // Calculate priority upon object creation
}

void Passengers::setSPType(string spType)
{
    SPType = spType;
}

void Passengers::setType(string t)
{
    type = t;
}

void Passengers::setArrivalTime(Time& aTime)
{
    arrivalTime.setTotalHours(aTime.getTotalHours());
    arrivalTime.setTotalMinutes(aTime.getTotalMinutes());
}

void Passengers::setOn_OffTime(int ooTime)
{
    On_OffTime = ooTime;
}

void Passengers::setStartStation(int startStat)
{
    startStation = startStat;
}

void Passengers::setEndStation(int endStat)
{
    endStation = endStat;
}

void Passengers::setMaxWaitingTime(int w)
{
    this->MaxWaitingTime = w;
}

void Passengers::setFinishedTime(Time t)
{
    this->FinishedTime.setTotalHours(t.getTotalHours());
    this->FinishedTime.setTotalMinutes(t.getTotalMinutes());
}

void Passengers::setMoveTime(Time t)
{
    this->MoveTime.setTotalHours(t.getTotalHours());
    this->MoveTime.setTotalMinutes(t.getTotalMinutes());
}


string Passengers::getSPType() const
{
    return SPType;
}

string Passengers::getType() const
{
    return type;
}

Time Passengers::getArrivalTime() const
{
    return arrivalTime;
}

int Passengers::getOn_OffTime() const
{
    return On_OffTime;
}

int Passengers::getStartStation() const
{
    return startStation;
}

int Passengers::getEndStation() const
{
    return endStation;
}

int Passengers::getMaxWaitingTime() const
{
    return this->MaxWaitingTime;
}

int Passengers::getID() const
{
    return this->ID;
}

Time Passengers::getFinishedTime() const
{
    return this->FinishedTime;
}

Time Passengers::getMoveTime() const
{
    return MoveTime;
}

Time Passengers::getWaitingTime() const
{
    return (MoveTime - arrivalTime);
}

Time Passengers::getTripTime() const
{
    return(FinishedTime - MoveTime);
}


void Passengers::calculatePriority()
{
    if (type == "SP") {
        if (SPType == "aged") {
            priority = 1;
            return;
        }
        if (SPType == "POD") {
            priority = 2;
            return;
        }
        if (SPType == "PREG") {
            priority = 3;
            return;
        }
    }
    if (type == "NP") {
        priority = 4;
        return;
    }
    if (type == "WP") return;
}

int Passengers::getPriority() const
{
    return priority;
}

void Passengers::setPriority(int pri)
{
    priority = pri;
}

//void Passengers::promoteNP()
//{
//
//    if (type == "NP" && WaitingTime.getTotalMinutes() == getMaxWaitingTime()) {
//        setPriority(1);
//    }
//}

Passengers& Passengers::operator=(const Passengers& P1)
{
    if (this != &P1) {
        type = P1.type;
        SPType = P1.SPType;
        ID = P1.ID;
        arrivalTime = P1.arrivalTime;
        On_OffTime = P1.On_OffTime;
        startStation = P1.startStation;
        endStation = P1.endStation;
        priority = P1.priority;
    }
    return *this;
}



ostream& operator<<(ostream& out, const Passengers& passenger)
{
    if (passenger.getSPType()!="") {
        if (passenger.getSPType() == "aged") {
            out << passenger.getID() << "(Ag)";
        }
        else if (passenger.getSPType() == "POD") {
            out << passenger.getID() << "(PD)";
        }
        else {
            out << passenger.getID() << "(Pg)";
        }

    }
    else {
        out << passenger.getID();

    }
    return out;
}

bool operator==(const Passengers& P1, int v)
{
    return (P1.getID() == v);
}
