#pragma once
#include "DEFS.h"
#include <iostream>
#include <windows.h>
#include "Time.h"
#include "Passengers.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include"List.h"
#include"Station.h"
#include "Bus.h"

using namespace std;
class UI
{
private:
	Mode mode; // Private member variable to store the current mode

public:
	// Default constructor
	UI();

	bool runMode();
	

	void setMode(Mode m);
	Mode getMode();



	// Getter for a file name
	string getFileName();

	// Display time in a specific format on the console
	void displayTime(Time t);

	// Display information about a station
	void displayStationInfo(Station& s);

	void displayCheckupList(Station& s);


	// Display the contents of a generic queue of passengers
	void displayQueue(Queue<Passengers*>& p);

	void displayfinishedPassengers(Queue<Passengers*>& p);
	// Display the contents of a priority queue of passengers
	void displayPQueue(PriorityQueue<Passengers*>& p);

	// Print separator lines for better console output formatting
	void printLines();

	// Print a message indicating a failed operation
	void printFailedMessage();

	// Display the finished passenger list from a generic queue
	void displayFinishedPassengerList(Queue<Passengers*> p);

	// Display a message indicating the next station
	void displayNextStationString();

	void displaybusInfoQueue(Queue<Bus*>& p);
	void displayBusQueue(Queue<Bus*>& p);

	void displayText(string s);


	// Function to wait for user input, providing a form of user interaction
	void awaitFunction();
};
