#pragma once
#include "Queue.h"
#include "PriorityQueue.h"
#include"Passengers.h"
#include"Bus.h"
#include<fstream>
#include"Station.h"
#include <random>
#include "DEFS.h"
#include "Time.h"
#include "List.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>     /* abs */
#include"UI.h"



class Event;
class UI;
class ArrivalEvent;
class LeaveEvent;
constexpr auto MaxStations = 100;
class Company
{
	//Private Data members of company class

	int stationNumber; //variable to hold the current station number
	int stationsPrinted;
	int totalStationNumber;
	int TimeBetweenStations;// variable to hold the time between each station
	int maxWaitingTime; // Max waiting time variable to be sent to the passenger when declarion

	int TotalWpBusNum; //Variable to hold the total number of wheel chair busses
	int TotalMBusNum; //Variable to hold the total number of Mixed chair busses

	int WpBusCapacity; //variable holding the maximum capacity of Wheel Chair busses
	int MBuscapacity; //Variable to hold the maximum capacity of Mixed Busses

	int NPCounter;
	int WPCounter;
	int SPCounter;
	int WBusCounter;
	int MBusCounter;

	int TripNumberBeforeMaintenance;
	int WbuscheckupDuration;
	int MbuscheeckupDuration;
	int arrivalCounter;

	int getOnOffTime;

	int EventNumber;
	string EventType;
	string PassengerType;

	int PassengerHour;
	int PassengerMinute;
	string SpecialPassengerType;
	int PassengerID;
	int StartStation;
	int EndStation;
	Bus* wbus;
	Bus* mbus;
	UI* UIptr;
	Time time;
	Time timer;
	//Station* stations;
	Queue<Passengers*>finishedPassengers;
	Queue<Event*> Events;
	Station stationArray[MaxStations];
	Queue<Bus*>WPbuses;
	Queue<Bus*>Mbuses;
	Queue<Bus*> MovingWpBusesF; //Queue For Moving WheelChair Busses FWD
	Queue<Bus*> MovingWpBusesB; //Queue for Moving WheelChair Busses BWD
	Queue<Bus*> MovingMBusesF; //Queue for Moving Mixed Busses FWD
	Queue<Bus*> MovingMBusesB; //Queue for Moving Mixed Busses BWD
	

public:
	//member functions

	//constructor
	Company();



	//functions to load file and assign variables
	void LoadFile();
	void readFile(ifstream& inFile);


	//functions to simulate and generate time steps
	void simulate();
	void generatetimeSteps();
	void incrementMins();

	//function too add passenger to their lists
	void addPassenger(Passengers* pass);
	void MoveFromStationsB();
	void MoveFromStationsF();
	void MoveWBusesF();
	void MoveMBusesF();
	void MoveWBusesB();
	void MoveMBusesB();
	//function to remove the passenger from their list in case of Leave Event
	void leavePassenger(int station,int id);
	void MoveBusesFromStationZero();
	//void MoveBusesToStationZero(Bus* bus);
	void setBusStatusForMaintainance(Bus* bus);
	void load_passengers();
	void unload_passengers();
	void DisplayMessage();
	void performCheckUp(Queue<Bus*>& wpMain, Queue<Bus*>& MMain);
	bool IsRemainingEvents();

	void performAutoPromotion();

	void saveFile();

	void applyFunctions();





	Queue<Passengers*>& getFinishedPassenger();
	//destructor
	~Company();
};