// Include necessary header files
#include "Company.h"
#include "ArrivalEvent.h"
#include "LeaveEvent.h"

// Constructor for the Company class
Company::Company()
{
    // Initialize member variables with default values
    time.setTotalHours(4);
    time.setTotalMinutes(0);
    UIptr = new UI();
    stationNumber = 0;
    totalStationNumber = 0;
    TimeBetweenStations = 0;
    maxWaitingTime = 0;

    // Initialize bus-related variables
    TotalWpBusNum = 0;
    TotalMBusNum = 0;
    WpBusCapacity = 0;
    MBuscapacity = 0;
    TripNumberBeforeMaintenance = 0;
    WbuscheckupDuration = 0;
    MbuscheeckupDuration = 0;

    // Initialize event-related variables
    getOnOffTime = 0;
    EventNumber = 0;
    EventType = "";

    // Initialize passenger-related variables
    PassengerType;
    PassengerHour = 0;
    PassengerMinute = 0;
    SpecialPassengerType = "";
    PassengerID = 0;
    StartStation = 0;
    EndStation = 0;
    stationsPrinted = 0;
}

Queue<Passengers*>& Company::getFinishedPassenger()
{
    return this->finishedPassengers;
}

// Load simulation parameters from a file
void Company::LoadFile()
{
    ifstream inFile(UIptr->getFileName() + ".txt");
    readFile(inFile);
}

// Read simulation parameters from a file
void Company::readFile(ifstream& inFile)
{
    // Check if the file is opened successfully
    if (inFile.fail())
    {
        UIptr->printFailedMessage();
    }

    // Read simulation parameters from the file
    inFile >> totalStationNumber >> TimeBetweenStations >> TotalWpBusNum >> TotalMBusNum >> WpBusCapacity >> MBuscapacity >> TripNumberBeforeMaintenance >> WbuscheckupDuration >> MbuscheeckupDuration >> maxWaitingTime >> getOnOffTime >> EventNumber;



    // Initialize stationArray with Station objects
    for (int i = 0; i <= totalStationNumber; ++i)
    {
        stationArray[i] = Station(i);
    }



    for (int i = 0; i < TotalWpBusNum; ++i)//Adding wpbuses to the Queue of the wpBuses
    {
        Bus* bus = new Bus(WpBusCapacity, WbuscheckupDuration, 0, TripNumberBeforeMaintenance, WHEELCHAIR,false,false,false,0);
        bus->setCurrentBusTime(timer);
        bus->setCurrentDestination(0);
        bus->setNextDestination(1);
        stationArray[0].AddwpBus(bus);
        WBusCounter++;
        WPbuses.enqueue(bus);

        //initiallising the number of the trips with zero and it should increament as the bus passes by each station


    }

    for (int i = 0; i < TotalMBusNum; ++i)//Adding Mbuses to the Queue of the MBuses
    {
        Bus* bus = new Bus(MBuscapacity, MbuscheeckupDuration, 0, TripNumberBeforeMaintenance, MIXED,false, false,false,0);
        bus->setCurrentBusTime(timer);
        bus->setCurrentDestination(0);
        bus->setNextDestination(1);
        stationArray[0].AddMBus(bus);
        MBusCounter++;
        Mbuses.enqueue(bus);

    }


    // Read and process events from the file
    for (int i = 0; i < EventNumber; i++)
    {
        inFile >> EventType;
        if (EventType == "A")
        {
            inFile >> PassengerType;
            // Check if the passenger type is special
            if (PassengerType == "SP")
            {
                char col;
                inFile >> PassengerHour >> col >> PassengerMinute >> PassengerID >> StartStation >> EndStation >> SpecialPassengerType;
                this->time.setTotalHours(PassengerHour);
                this->time.setTotalMinutes(PassengerMinute);
                // Create an ArrivalEvent and enqueue it
                ArrivalEvent* arrive = new ArrivalEvent(time, PassengerType, PassengerID, StartStation, EndStation, getOnOffTime, SpecialPassengerType);
                Events.enqueue(arrive);
                arrivalCounter++;
                SPCounter++;
            }
            else
            {
                char col;
                inFile >> PassengerHour >> col >> PassengerMinute >> PassengerID >> StartStation >> EndStation;
                this->time.setTotalHours(PassengerHour);
                this->time.setTotalMinutes(PassengerMinute);
                // Create an ArrivalEvent and enqueue it
                ArrivalEvent* arrive = new ArrivalEvent(time, PassengerType, PassengerID, StartStation, EndStation, getOnOffTime);
                Events.enqueue(arrive);
                arrivalCounter++;
                if (PassengerType == "WP") {
                    WPCounter++;
                }
                else {
                    NPCounter++;
                }

            }
        }
        else
        {
            char col;
            inFile >> PassengerHour >> col >> PassengerMinute >> PassengerID >> StartStation;
            this->time.setTotalHours(PassengerHour);
            this->time.setTotalMinutes(PassengerMinute);
            // Create a LeaveEvent and enqueue it
            LeaveEvent* leave = new LeaveEvent(time, PassengerID, StartStation);
            Events.enqueue(leave);
        }
    }
}

// Simulate the bus system
void Company::simulate()
{
    LoadFile();
    bool is_ValidMode=UIptr->runMode();
    int totalMinutes = timer.toTotalMinutes();
    if (is_ValidMode) {
        UIptr->displayText("Simulation Started! \n");

        while (totalMinutes <= 1380)
        {
            MoveBusesFromStationZero();
            generatetimeSteps();

            if (UIptr->getMode() == Silent) {
                applyFunctions();
            }
            else {
                UIptr->awaitFunction();
                UIptr->displayTime(timer);

                for (int i = 0; i <= totalStationNumber; i++) {
                    UIptr->displayStationInfo(stationArray[i]);
                    UIptr->displayCheckupList(stationArray[0]);
                    UIptr->displayfinishedPassengers(finishedPassengers);
                }

                applyFunctions();
            }

            totalMinutes = timer.toTotalMinutes(); // Update totalMinutes
        }
        Sleep(1000);
        saveFile();
        UIptr->displayText("Simulation ends, output file generated.\n");
    }
    else {
        return;
    }
   
}


// Generate time steps and execute events
void Company::generatetimeSteps()
{
    Event* nxt;

    while (Events.peek(nxt) && nxt->GetTime() == timer)
    {

        Events.dequeue(nxt);
        stationNumber = nxt->GetCurrentStation();
        nxt->excute(this);
        if (UIptr->getMode() == Interactive) {

        DisplayMessage();
        }

        // Deallocate event after execution
        delete nxt;
    }

}


// Increment time by one minute
void Company::incrementMins()
{
    timer.incrementTotalMinutes();
}

// Add a passenger to a station
void Company::addPassenger(Passengers* pass)
{
    stationArray[pass->getStartStation()].Addpassenger(pass);
}

void Company::MoveFromStationsB()
{
    for (int i = totalStationNumber; i >= 1; i--) {
        if (stationArray[i].getWaitingMixedBusB().peek(mbus)) {
            if (!mbus->getIsLoading() && !mbus->getIsUnloading()) {
                stationArray[i].RemoveMbusB(mbus);
                MovingMBusesB.enqueue(mbus);
                mbus->setBusMoveTime(timer);
                mbus->setCurrentBusTime(timer);
                mbus->setCurrentDestination(i);

                if (i - 1 == 0) {
                    mbus->setNextDestination(i + 1);
                    setBusStatusForMaintainance(mbus);
                }
                else {

                    mbus->setNextDestination(i - 1);
                }
            }
        }
        if (stationArray[i].getWaitingWheelBusB().peek(wbus)) {
            if (!wbus->getIsLoading() && !wbus->getIsUnloading()) {
                stationArray[i].RemoveWbusB(wbus);
                MovingWpBusesB.enqueue(wbus);
                wbus->setBusMoveTime(timer);

                wbus->setCurrentBusTime(timer);
                wbus->setCurrentDestination(i);
                if (i - 1 == 0) {
                    wbus->setNextDestination(i + 1);
                    setBusStatusForMaintainance(wbus);
                }
                else {
                    wbus->setNextDestination(i - 1);
                }
            }
        }
    }
}

void Company::MoveFromStationsF()
{
    
    for (int i = 1; i <= totalStationNumber; i++) {
        if (stationArray[i].getWaitingMixedBusF().peek(mbus)) {
            if (!mbus->getIsLoading() && !mbus->getIsUnloading()) {

                stationArray[i].RemoveMbusF(mbus);
                mbus->setCurrentDestination(i);
                if (i + 1 > totalStationNumber) {
                    MovingMBusesF.enqueue(mbus);
                    mbus->setBusMoveTime(timer);

                    mbus->setCurrentBusTime(timer);
                    mbus->setNextDestination(totalStationNumber - 1);
                    setBusStatusForMaintainance(mbus);
                }
                else {
                    MovingMBusesF.enqueue(mbus);
                    mbus->setBusMoveTime(timer);
                    mbus->setCurrentBusTime(timer);
                    mbus->setNextDestination(i + 1);
                }
            }
        }
        if (stationArray[i].getWaitingWheelBusF().peek(wbus)) {
            if (!wbus->getIsLoading() && !wbus->getIsUnloading()) {


                stationArray[i].RemoveWbusF(wbus);
                MovingWpBusesF.enqueue(wbus);

                wbus->setBusMoveTime(timer);

                wbus->setCurrentBusTime(timer);
                wbus->setCurrentDestination(i);
                if (i + 1 > totalStationNumber) {
                    wbus->setNextDestination(totalStationNumber - 1);
                    setBusStatusForMaintainance(wbus);

                }
                else {
                    wbus->setNextDestination(i+1);
                }
            }

        }
    }
}

// Remove a passenger from a station
void Company::leavePassenger(int stStation, int id)
{
    if (stationArray[stStation].removePassengerUsingID(stationArray[stStation].getNormalPassengerB(), id)) return;
    if (stationArray[stStation].removePassengerUsingID(stationArray[stStation].getNormalPassengerF(), id)) return;
    if (stationArray[stStation].removePassengerUsingID(stationArray[stStation].getWheelChairPassengerF(), id)) return;
    if (stationArray[stStation].removePassengerUsingID(stationArray[stStation].getWheelChairPassengerB(), id)) return;
    if (stationArray[stStation].removeSpecialPassengerUsingId(stationArray[stStation].getSpecialPassengerF(), id)) return;
    if (stationArray[stStation].removeSpecialPassengerUsingId(stationArray[stStation].getSpecialPassengerB(), id)) return;
}

void Company::MoveBusesFromStationZero()
{
    static bool isWBusTurn = true;

    if (timer.toTotalMinutes() % 15 == 0)
    {
        if (isWBusTurn)
        {
            if (!stationArray[0].RemoveWbusF(wbus))
            {
                // If WBus queue is empty, remove MBus
                if (stationArray[0].RemoveMbusF(mbus)) {
                MovingMBusesF.enqueue(mbus);
                mbus->setCurrentBusTime(timer);
                mbus->setCurrentDestination(0);
                mbus->setNextDestination(1);
                }

            }
            else
            {
                MovingWpBusesF.enqueue(wbus);
                wbus->setCurrentBusTime(timer);
                wbus->setCurrentDestination(0);
                wbus->setNextDestination(1);

            }
        }
        else
        {
            if (!stationArray[0].RemoveMbusF(mbus))
            {
                // If MBus queue is empty, remove WBus
                if (stationArray[0].RemoveWbusF(wbus)) {

                wbus->setCurrentBusTime(timer);

                MovingWpBusesF.enqueue(wbus);
                wbus->setCurrentDestination(0);
                wbus->setNextDestination(1);
               }

            }
            else
            {
                MovingMBusesF.enqueue(mbus);
                mbus->setCurrentBusTime(timer);
                mbus->setCurrentDestination(0);
                mbus->setNextDestination(1);

            }
        }

        isWBusTurn = !isWBusTurn; // Switch between WBus and MBus turn
    }
}




void Company::setBusStatusForMaintainance(Bus* bus)
{
    if (bus->getBusType() == WHEELCHAIR)
    {
        if (MovingWpBusesF.peek(bus))
        {
            if (bus->getTrips() == TripNumberBeforeMaintenance)
            {
                bus->setgoingForMaintainance(true);
                bus->setNextDestination(0);
            }
        }
      
        if (MovingWpBusesB.peek(bus))
        {
            if (bus->getTrips() == TripNumberBeforeMaintenance)
            {
                bus->setgoingForMaintainance(true);
                bus->setNextDestination(0);
            }
        }
       
        
    }
    if (bus->getBusType() == MIXED)
    {
        if (MovingMBusesF.peek(bus))
        {
            if (bus->getTrips() == TripNumberBeforeMaintenance)
            {
                bus->setgoingForMaintainance(true);
                bus->setNextDestination(0);
            }
        }
        if (MovingMBusesB.peek(bus))
        {
            if (bus->getTrips() == TripNumberBeforeMaintenance)
            {
                bus->setgoingForMaintainance(true);
                bus->setNextDestination(0);
            }
        }



    }


}



void Company::MoveWBusesF()
{

    for (int i = 1; i <= totalStationNumber; i++) {
        if (MovingWpBusesF.peek(wbus)) {
            if (!wbus->isMaintenanceRequired() )
            {
                
                if ((wbus->getCurrentBusTime() + TimeBetweenStations) == timer && wbus->getNextDestination() == i) {
                    if (i + 1 > totalStationNumber) {
                        wbus->setCurrentDestination(i);
                        wbus->setNextDestination(totalStationNumber - 1);
                        wbus->incrementTrips();
                        wbus->setDirection("BCK");

                    }
                    stationArray[i].AddwpBus(wbus);
                    MovingWpBusesF.dequeue(wbus);  // Remove bus from moving queue
                }
            }
            else
            {
                if (wbus->getCurrentBusTime() + (TimeBetweenStations* (wbus->getCurrentDestination())) == timer)
                {
                    stationArray[0].AddWPMaintaiance(wbus);
                    MovingWpBusesF.dequeue(wbus);
                }
            }
        }
    }

}//each bus should hold the time where it started moving so that i can calculate when to add that bus in another station

void Company::MoveMBusesF()
{

    for (int i = 1; i <= totalStationNumber; i++) {
        if (MovingMBusesF.peek(mbus)) {
            if (!mbus->isMaintenanceRequired())
            {
                if ((mbus->getCurrentBusTime() + TimeBetweenStations) == timer && mbus->getNextDestination() == i) {
                    if (i + 1 > totalStationNumber) {
                        mbus->setCurrentDestination(i);
                        mbus->setNextDestination(totalStationNumber - 1);
                        mbus->incrementTrips();
                        mbus->setDirection("BCK");


                    }
                    stationArray[i].AddMBus(mbus);
                    MovingMBusesF.dequeue(mbus);  // Remove bus from moving queue
                }
            }
            else
            {
                if (mbus->getCurrentBusTime() + (TimeBetweenStations * (mbus->getCurrentDestination())) == timer)
                {
                    stationArray[0].AddMMaintaiance(mbus);
                    MovingMBusesF.dequeue(wbus);
                }
            }
        }
    }

}//each bus should hold the time where it started moving so that i can calculate when to add that bus in another station




void Company::MoveWBusesB()
{
    for (int i = totalStationNumber; i >= 1; i--) {
        if (MovingWpBusesB.peek(wbus)) {
            if (!wbus->isMaintenanceRequired())
            {
                if ((wbus->getCurrentBusTime() + TimeBetweenStations) == timer && wbus->getNextDestination() == i) {
                    if (i - 1 == 0) {
                        wbus->setCurrentDestination(i);
                        wbus->setNextDestination(i + 1);
                        wbus->incrementTrips();
                        wbus->setDirection("FWD");


                    }
                    stationArray[i].AddwpBus(wbus);
                    MovingWpBusesB.dequeue(wbus);  // Remove bus from moving queue
                }
            }
            else
            {
                if (wbus->getCurrentBusTime() + (TimeBetweenStations * (wbus->getCurrentDestination())) == timer)
                {
                    stationArray[0].AddWPMaintaiance(wbus);
                    MovingWpBusesB.dequeue(wbus);
                }
            }
        }
    }
}


void Company::MoveMBusesB()
{
    for (int i = totalStationNumber; i >= 1; i--) {
        if (MovingMBusesB.peek(mbus)) {
            if (!mbus->isMaintenanceRequired())
            {
                if ((mbus->getCurrentBusTime() + TimeBetweenStations) == timer && mbus->getNextDestination() == i) {
                    if (i - 1 == 0) {
                        mbus->setCurrentDestination(i);
                        mbus->setNextDestination(i + 1);
                        mbus->incrementTrips();
                        mbus->setDirection("FWD");

                    }
                    stationArray[i].AddMBus(mbus);
                    MovingMBusesB.dequeue(mbus);  // Remove bus from moving queue
                }
            }
            else
            {
                if (mbus->getCurrentBusTime() + (TimeBetweenStations * (mbus->getCurrentDestination())) == timer)
                {
                    stationArray[0].AddMMaintaiance(mbus);
                    MovingMBusesB.dequeue(wbus);
                }
            }
        }
    }
}




void Company::load_passengers()
{
    for (int i = 1; i <= totalStationNumber; i++)
    {
        if (stationArray[i].getWaitingWheelBusF().peek(wbus) && !wbus->getIsUnloading() && timer.toTotalMinutes()<=1320)//checks first if the first bus at the queue of waiting buses has successfully unloaded or not
        {
            stationArray[i].loadWpPassOnBusF();
        }
        if (stationArray[i].getWaitingWheelBusB().peek(wbus) && !wbus->getIsUnloading() && timer.toTotalMinutes() <= 1320)
        {
            stationArray[i].loadWpPassOnBusB();
        }
        if (stationArray[i].getWaitingMixedBusF().peek(mbus) && !mbus->getIsUnloading() && timer.toTotalMinutes() <= 1320)
        {
            stationArray[i].loadMPassOnBusF();
        }
        if (stationArray[i].getWaitingMixedBusB().peek(mbus) && !mbus->getIsUnloading() && timer.toTotalMinutes() <= 1320)
        {
            stationArray[i].loadMPassOnBusB();
        }
    }
    

}

void Company::unload_passengers()
{
    for (int i = 1; i <= totalStationNumber; i++)
    {
        stationArray[i].unloadWpPassOffBusF(finishedPassengers, timer);
        stationArray[i].unloadWpPassOffBusB(finishedPassengers,timer);
        stationArray[i].unloadMPassOffBusF(finishedPassengers,timer);
        stationArray[i].unloadMPassOffBusB(finishedPassengers,timer);
    }


}




// Display a message to prompt the user to move to the next station
void Company::DisplayMessage()
{
    UIptr->displayNextStationString();
}

void Company::performCheckUp(Queue<Bus*> &wpMain, Queue<Bus*>& MMain)
{
        if (wpMain.peek(wbus))
        {
            if (wbus->getTimeInMaintainance() < WbuscheckupDuration)
            {
                wbus->increamentTimeInMaintainance();
                wbus->setCurrentDestination(0);
            }
            else
            {
                wpMain.dequeue(wbus);
                wbus->setNextDestination(1);
                
                wbus->setTrips(0);
                wbus->resetTimeInMaintainance();
                wbus->setCurrentBusTime(timer);
                MovingWpBusesF.enqueue(wbus);
            }
        }

        if (MMain.peek(mbus))
        {

            if (mbus->getTimeInMaintainance() < MbuscheeckupDuration)
            {
                mbus->increamentTimeInMaintainance();
                mbus->setCurrentDestination(0);
            }
            else
            {
                MMain.dequeue(mbus);
                mbus->setNextDestination(1);
                mbus->setTrips(0);
                mbus->resetTimeInMaintainance();
                mbus->setCurrentBusTime(timer);
                MovingMBusesF.enqueue(mbus);
            }

        }

}



// Check if there are remaining events in the event queue
bool Company::IsRemainingEvents()
{
    int eventSize = Events.GetSize();
    return (eventSize > 0);
}

void Company::performAutoPromotion()
{
    for (int i = 1; i <= totalStationNumber; i++) {
        stationArray[i].autoPromote(stationArray[i].getSpecialPassengerB(), stationArray[i].getNormalPassengerB(), timer);
        stationArray[i].autoPromote(stationArray[i].getSpecialPassengerF(), stationArray[i].getNormalPassengerF(), timer);
    }
}

void Company::saveFile()
{
    ofstream fout("save.txt");
    Passengers* Pptr = nullptr;
    float totalWaitingTime = 0.0;
    float totalTripTime = 0.0;
    Time tW;
    Time tT;
    double counter = 0.0;
    double percentageOfPromoted = 0.0;
    fout << "FT\t\tID\t\tAT\t\tWT\n";
    for (int i = 0; i < (NPCounter + SPCounter + WPCounter); i++) {
        finishedPassengers.dequeue(Pptr);
        fout << Pptr->getFinishedTime().getTotalHours() << ":" << Pptr->getFinishedTime().getTotalMinutes() << "\t\t" << Pptr->getID() << "\t\t" << Pptr->getArrivalTime().getTotalHours() << ":" << Pptr->getArrivalTime().getTotalMinutes() << "\t\t";
        fout << Pptr->getWaitingTime().getTotalHours() << ":" << Pptr->getWaitingTime().getTotalMinutes() << "\n";
        totalWaitingTime += Pptr->getWaitingTime().toTotalMinutes();
        totalTripTime += Pptr->getTripTime().toTotalMinutes();

    }
    for (int i = 1; i <= totalStationNumber; i++) {
        counter += stationArray[i].getAutoPromotedCounter();
    }

    fout << "passesngers: " << (NPCounter + SPCounter + WPCounter) << "[NP:" << NPCounter << ", SP : " << SPCounter << ", WP : " << WPCounter << "]\n";
    tW.fromTotalMinutes((totalWaitingTime / (NPCounter + SPCounter + WPCounter)));
    tT.fromTotalMinutes((totalTripTime / (NPCounter + SPCounter + WPCounter)));

    fout << "passesngers Avg Wait time= " << tW.getTotalHours() << ":" << tW.getTotalMinutes() << "\n";
    fout << "passesngers Avg trip time= " << tT.getTotalHours() << ":" << tT.getTotalMinutes() << "\n";
    percentageOfPromoted = (counter / (NPCounter));
    fout << "Auto-promoted passesngers= " << percentageOfPromoted *100 << "%" << "\n";
    fout << "buses: " << (WBusCounter + MBusCounter) << "[WBus:" << WBusCounter << ", MBus : " << MBusCounter << "]\n";



}


void Company::applyFunctions()
{
    stationNumber++;
    stationsPrinted++;
    incrementMins();
    MoveFromStationsF();
    MoveFromStationsB();
    MoveWBusesF();
    MoveMBusesF();
    MoveWBusesB();
    MoveMBusesB();
    unload_passengers();
    load_passengers();
    performCheckUp(stationArray[0].getWpMaintainance(), stationArray[0].getMMaintainance());
    performAutoPromotion();
}

// Destructor for the Company class
Company::~Company()
{
    delete UIptr;  // Deallocate the UIptr object
    while (!WPbuses.isempty()) {
        WPbuses.dequeue(wbus);
        delete wbus;
    }

    while (!Mbuses.isempty()) {
        Mbuses.dequeue(mbus);
        delete mbus;
    }

}
