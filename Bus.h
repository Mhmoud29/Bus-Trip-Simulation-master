#pragma once
#include "PriorityQueue.h"
#include "Passengers.h"
#include "DEFS.h"
#include "Time.h"
#include <cmath>
#include <iostream>

class Bus {
private:
    
    Time expectedArrival;//$
    BusType bustype;
    Time busyTime;
    Time currentBusTime;
    Time busMoveTime;
    PriorityQueue<Passengers*> passengerList;


    const int tripsToMaintenance;
    int bId;
    static int nextBusId;  // Static data member to store the next available bus ID

    int max_capacity;
    int currentCapacity;
    int maintenanceTime;
    int move_time;
    int moving_passenger;
    int trips; //to go from station 1 to N or from N to 1 is counted as 1 trip
    int next_destination;
    int currentStation;
    bool goingForMaintainance;

    int timeInMaintainance;
    float utilization;
    bool isUnloading;
    bool isLoading;

    string direction;

public:
    // Constructor
    Bus(int cap, int maintT, int t, int MaxTrips, BusType type,bool ul,bool l,bool m,int main);

    // Destructor
    ~Bus() {}

    //setters
    void setMaxCap(int);
    void setMaint(int);
    void setTrips(int);
    void setCurrentBusTime(Time t);
    void setgoingForMaintainance(bool i);
    void resetTimeInMaintainance();
    void setDirection(string d);
    void setBusMoveTime(Time t);

    //gett the Bus ID
    int getBusID();

    //get the driection
    string getDirection();


    void increamentTimeInMaintainance();
    Time getCurrentBusTime();
    int getTimeInMaintainance();

    // Functions to load and Unload a passenger onto/from the bus
    void load(Passengers* passenger);
    bool unload();


    //setter and getter for the bus unloading status
    void setIsUnLoading(bool ul);
    bool getIsUnloading();

    void setIsLoading(bool l);
    bool getIsLoading();

    //busy time function
    void busBusyTime();
    Time getBusBusyTime();
    Time calculateTotalBusyTime();

    //currentCap
    bool incrementCurrentCap();
    void decrementCurrentCap();
    int getCurrentCap();


    // Getter functions
    int getMaxCap() const;
    int getMaint() const;
    int getTrips() const;
    bool getgoingForMaintainance() const;
    BusType getBusType() const;
    Time getBusMoveTime() const;

    // Methods for maintenance and trip tracking
    void incrementTrips();
    bool isMaintenanceRequired() const;
    void performMaintenance();

    //setters and getters for the Busses Distinations
    void setNextDestination(int n);
    void setCurrentDestination(int c);

    int getNextDestination();
    int getCurrentDestination();

    PriorityQueue<Passengers*>& getpassengerList();
    friend ostream& operator<<(ostream& out, const Bus& bus);


};
