#pragma once
#include<iostream>
#include"Time.h"
#include "DEFS.h"

using namespace std;

class Passengers {
private:
    string SPType;
    string type;
    int ID; //unique Id
    int BusId;
    Time arrivalTime;
    Time WaitingTime;
    Time FinishedTime;
    Time MoveTime;
    Time TripTime;
    int MaxWaitingTime;
    int On_OffTime;
    int startStation;
    int endStation;
    int priority;

public:
    // Constructors
    Passengers();
    Passengers(string s, Time& aTime, int ooTime, int startStat, int endStat,int Id);
    Passengers(string t, Time& aTime, int ooTime, int startStat, int endStat, string spType,int id);


    // Setters
    void setSPType(string spType);
    void setType(string t);
    void setArrivalTime(Time& aTime);
    void setOn_OffTime(int ooTime);
    void setStartStation(int startStat);
    void setEndStation(int endStat);
    void setMaxWaitingTime(int w);
    void setFinishedTime(Time t);
    void setMoveTime(Time t);


    // Getters
    string getSPType() const;
    string getType() const;
    Time getArrivalTime() const;
    int getOn_OffTime() const;
    int getStartStation() const;
    int getEndStation() const;
    int getMaxWaitingTime()const;
    int getID() const;
    Time getFinishedTime() const;
    Time getMoveTime()const;
    Time getWaitingTime() const;
    Time getTripTime() const;


    // Calculate Priority
    void calculatePriority();
    int getPriority() const;
    void setPriority(int pri);

    ////np wait time special function
    //void promoteNP();

    //Overloading
    friend ostream& operator<<(ostream& out, const Passengers& passenger);
    Passengers& operator=(const Passengers& P1);
    friend bool operator==(const Passengers& P1, int v);
    // Destructor
    ~Passengers() {}
};
