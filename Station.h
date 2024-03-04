#pragma once
#include "Time.h"
#include "DEFS.h"
#include "Passengers.h"
#include "Queue.h"
#include "priorityQueue.h"
#include "bus.h"
#include"List.h"
#include<iostream>
#include"BST.h"
using namespace std;

class Station
{
private:
	//Private data members
	int stationNumber; //data member to store the the station number
	int counterOfAutoPromoted;
	//Queues used to store the forward and backward passengers in different Queues
	Queue<Passengers*>NPpassengersF;
	Queue<Passengers*>WPpassengersF;
	Queue<Passengers*>NPpassengersB;
	Queue<Passengers*>WPpassengersB;

	//PriorityQueues used to store the forward and backward Special passengers in different Queues
	PriorityQueue<Passengers*>SPpassengersF;
	PriorityQueue<Passengers*>SPpassengersB;

	//Queue for passengers who have arrived at the station from a bus
	Queue<Passengers*>ArrivedPass;
	//Queue to store the busses
	//Queue<Bus*> WPbus;
	//Queue<Bus*> Mbus;
	Queue<Bus*> WPMaintainance; //Queue for the WheelChair Buses in Maintainance
	Queue<Bus*> MMaintainance; //Queue for the Mixed Buses in Maintainance
	Queue<Bus*> waitingMBusF; //Queue for waiting FWD Mixed Buses in the station 
	Queue<Bus*> waitingMBusB; //Queue for waiting BWD Mixed Buses in the station
	Queue<Bus*> waitingWBusF; //Queue for waiting FWD WheelChair Buses in the station
	Queue<Bus*> waitingWBusB; //Queue for waiting BWD WheelChair Buses in the station

public:
	//constructor
	Station();
	Station(int snumber);


	//setters
	void setStationNum(int snum);
	int getStationNum();

	//Getters
	Queue<Passengers*>& getNormalPassengerF();
	Queue<Passengers*>& getNormalPassengerB();
	Queue<Passengers*>& getWheelChairPassengerF();
	Queue<Passengers*>& getWheelChairPassengerB();
	PriorityQueue<Passengers*>& getSpecialPassengerF();
	PriorityQueue<Passengers*>& getSpecialPassengerB();

	Queue<Passengers*>& getArrivedPassengers(); 
	Queue<Bus*>& getWpMaintainance();
	Queue<Bus*>& getMMaintainance();
	Queue<Bus*>& getWaitingWheelBusF();
	Queue<Bus*>& getWaitingWheelBusB();
	Queue<Bus*>& getWaitingMixedBusF();
	Queue<Bus*>& getWaitingMixedBusB();

	//Function to add passengers to the station
	void Addpassenger(Passengers* passenger);
	void AddwpBus(Bus* bus);
	void AddMBus(Bus* bus);
	void AddWPMaintaiance(Bus* bus);
	void AddMMaintaiance(Bus* bus);

	//Functions to remove the buses according to their direction
	bool RemoveMbusF(Bus* &buss);
	bool RemoveMbusB(Bus* &buss);

	bool RemoveWbusF(Bus* &buss);
	bool RemoveWbusB(Bus* &buss);

	bool RemoveWPMaintainance(Bus* bus);
	bool RemoveMMaintainance(Bus* bus);
	//Functions to remove the passengers from the queue using the ID
	bool removePassengerUsingID(Queue<Passengers*>&p, int id);
	bool removeSpecialPassengerUsingId(PriorityQueue<Passengers*>& p, int id);
	
	//Functions to return the total count of both forward and backward queues
	int returnTotalNormalCount();
	int returnTotalWheelChairCount();
	int returnTotalSpecialCount();
	int returnTotalWaitingBusCounts();
	int returnTotalBusINCheckUp();
	//functions to load passengers on the bus
	void loadWpPassOnBusF();
	void loadWpPassOnBusB();
	void loadMPassOnBusF();
	void loadMPassOnBusB();
	//functions to unload passengers of the bus
	void unloadWpPassOffBusF(Queue<Passengers*> &finishlist,Time timer);
	void unloadWpPassOffBusB(Queue<Passengers*> &finishlist,Time timer);
	void unloadMPassOffBusF(Queue<Passengers*> &finishlist,Time timer);
	void unloadMPassOffBusB(Queue<Passengers*> &finishlist, Time timer);


	//Auto promotion
	void incrementAutoPromoted();
	int getAutoPromotedCounter();
	void autoPromote(PriorityQueue<Passengers*>& special, Queue<Passengers*>& normal, Time timer);

	/*void AddBus(Bus* bus);
	void RemoveBus();*/
};