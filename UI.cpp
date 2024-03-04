#include "UI.h"

// Default constructor
UI::UI()
{
	mode = {}; // Initialize mode with default value
}

bool UI::runMode()
{
	int modeType;
	cout << "Enter the Mode Number (1 for Interactive, 2 for Silent): ";
	cin >> modeType;
	cout << endl;

	if (modeType == 1)
	{
		setMode(Interactive);
		return true;
	}
	else if (modeType == 2)
	{
		setMode(Silent);
		return true;

	}
	else
	{
		cout << "Invalid mode selection." << endl;
		return false;

	}

}



void UI::setMode(Mode m)
{
	this->mode = m;
}

Mode UI::getMode()
{
	return mode;
}




// Get a file name from user input
string UI::getFileName()
{
	string fileName;
	cout << "Enter the File Name: ";
	cin >> fileName;
	cout << endl;
	return fileName;
}

// Display time in a specific format on the console
void UI::displayTime(Time t)
{
	cout << "Current Time (Hr:Min)==> " << t.getTotalHours() << " : " << t.getTotalMinutes() << endl;
}

// Display information about a station and its waiting passengers
void UI::displayStationInfo(Station& s)
{
	
	cout << "================      " << "STATION #" << s.getStationNum() << "      ================" << endl;
	cout << s.returnTotalSpecialCount() << " Waiting SP: " << "FWD[";
	displayPQueue(s.getSpecialPassengerF());
	cout << "]";
	cout << "BCK[";
	displayPQueue(s.getSpecialPassengerB());
	cout << "]" << endl;

	cout << s.returnTotalWheelChairCount() << " Waiting WP: " << "FWD[";
	displayQueue(s.getWheelChairPassengerF());
	cout << "]";
	cout << "BCK[";
	displayQueue(s.getWheelChairPassengerB());
	cout << "]" << endl;

	cout << s.returnTotalNormalCount() << " Waiting NP: " << "FWD[";
	displayQueue(s.getNormalPassengerF());
	cout << "]";
	cout << "BCK[";
	displayQueue(s.getNormalPassengerB());
	cout << "]" << endl;

	cout << s.returnTotalWaitingBusCounts() << " Buses at this Station: " << endl;
	displaybusInfoQueue(s.getWaitingMixedBusF());
	displaybusInfoQueue(s.getWaitingMixedBusB());
	displaybusInfoQueue(s.getWaitingWheelBusF());
	displaybusInfoQueue(s.getWaitingWheelBusB());
	




	

}

void UI::displayCheckupList(Station& s) {
	printLines();
	cout << s.returnTotalBusINCheckUp() << " In-Checkup buses: ";
	displayBusQueue(s.getMMaintainance());
	displayBusQueue(s.getWpMaintainance());
	cout << endl;
	printLines();
}

// Display the contents of a generic queue of passengers
void UI::displayQueue(Queue<Passengers*>& p)
{
	Passengers* temp;
	Queue<Passengers*> copyQ(p);
	while (!copyQ.isempty())
	{
		if (copyQ.GetSize() == 1)
		{
			copyQ.dequeue(temp);
			std::cout << *temp;
		}
		else
		{
			copyQ.dequeue(temp);
			std::cout << *temp << ", ";
		}
	}
}

void UI::displayfinishedPassengers(Queue<Passengers*>& p)
{
	cout<<p.GetSize()<<" finshed passengers:";
	displayQueue(p);
	cout << "" << endl;
}



void UI::displayBusQueue(Queue<Bus*>& p) {
	Bus* temp;
	Queue<Bus*> copyQ(p);
	while (!copyQ.isempty())
	{
		if (copyQ.GetSize() == 1)
		{
			copyQ.dequeue(temp);
			std::cout << *temp;
		}
		else
		{
			copyQ.dequeue(temp);
			std::cout << *temp << ", ";
		}
	}
}

void UI::displayText(string s)
{
	cout << s;
}

// Display the contents of a generic queue of passengers
void UI::displaybusInfoQueue(Queue<Bus*>& p)
{
	Bus* temp;
	Queue<Bus*> copyQ(p);
	while (!copyQ.isempty())
	{
		if (copyQ.GetSize() == 1)
		{
			copyQ.dequeue(temp);
			if ((*temp).getBusType() == MIXED) {
				std::cout << "B" << *temp << "[" << (*temp).getDirection() << ", " << "MBus, " << (*temp).getMaxCap() << "] " << "{";
				displayPQueue((*temp).getpassengerList());
				std::cout << "}" << std::endl;
			}
			else {
				std::cout << "B" << *temp << "[" << (*temp).getDirection() << ", " << "WBus, " << (*temp).getMaxCap() << "] " << "{";
				displayPQueue((*temp).getpassengerList());
				std::cout << "}"<<std::endl;
			}
		}
		else
		{
			copyQ.dequeue(temp);

			if ((*temp).getBusType() == MIXED) {
				std::cout << "B" << *temp << "[" << (*temp).getDirection() << ", " << "MBus, " << (*temp).getMaxCap() << "] " << "{";
				displayPQueue((*temp).getpassengerList());
				std::cout << "}" << std::endl;
			}
			else {
				std::cout << "B" << *temp << "[" << (*temp).getDirection() << ", " << "WBus, " << (*temp).getMaxCap() << "] " << "{";
				displayPQueue((*temp).getpassengerList());
				std::cout << "}" << std::endl;
			}
		}
	}
}

// Display the contents of a priority queue of passengers
void UI::displayPQueue(PriorityQueue<Passengers*>& p)
{
	Passengers* temp;
	PriorityQueue<Passengers*> copyQ(p);

	while (!copyQ.isEmpty())
	{
		if (copyQ.getCount() == 1)
		{
			copyQ.deQueue(temp);
			std::cout << *temp;
		}
		else
		{
			copyQ.deQueue(temp);
			std::cout << *temp << ", ";
		}
	}
}

// Print separator lines for better console output formatting
void UI::printLines()
{
	cout << "------------------------------------------------------" << endl;
}

// Print a message indicating a failed operation
void UI::printFailedMessage()
{
	cout << "Failed to read the Text file/ file does not exist." << endl;
}

// Display the finished passenger list from a generic queue
void UI::displayFinishedPassengerList(Queue<Passengers*> p)
{
	cout << p.GetSize() << " finished passengers: ";
	displayQueue(p);
	cout << endl;
}

// Display a message indicating the next station
void UI::displayNextStationString()
{
	cout << "Press Any Key to display the next station" << endl;
}









// Function to wait for user input, providing a form of user interaction
void UI::awaitFunction()
{
	if (mode == Interactive)
	{
		cin.get();
	}
	if (mode == Silent)
	{
		Sleep(1000);
	}
}
