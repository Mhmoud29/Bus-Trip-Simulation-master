#include "Station.h"

// Default constructor
Station::Station()
{
    counterOfAutoPromoted = 0;
}

// Parameterized constructor with station number
Station::Station(int snumber)
{
    setStationNum(snumber);
    counterOfAutoPromoted = 0;

}

// Set station number
void Station::setStationNum(int snum)
{
    stationNumber = snum;
}

// Get station number
int Station::getStationNum()
{
    return stationNumber;
}

// Getters for different passenger queues
Queue<Passengers*>& Station::getNormalPassengerF()
{
    return this->NPpassengersF;
}

Queue<Passengers*>& Station::getNormalPassengerB()
{
    return this->NPpassengersB;
}

Queue<Passengers*>& Station::getWheelChairPassengerF()
{
    return this->WPpassengersF;
}

Queue<Passengers*>& Station::getWheelChairPassengerB()
{
    return this->WPpassengersB;
}

PriorityQueue<Passengers*>& Station::getSpecialPassengerF()
{
    return this->SPpassengersF;
}

PriorityQueue<Passengers*>& Station::getSpecialPassengerB()
{
    return this->SPpassengersB;
}

Queue<Passengers*>& Station::getArrivedPassengers()
{
    return this->ArrivedPass;
}

Queue<Bus*>& Station::getWpMaintainance()
{
    return this->WPMaintainance;
}

Queue<Bus*>& Station::getMMaintainance()
{
    return this->MMaintainance;
}

Queue<Bus*>& Station::getWaitingWheelBusF()
{
    return waitingWBusF;
}

Queue<Bus*>& Station::getWaitingWheelBusB()
{
    return waitingWBusB;
}

Queue<Bus*>& Station::getWaitingMixedBusF()
{
    return waitingMBusF;
}

Queue<Bus*>& Station::getWaitingMixedBusB()
{
    return waitingMBusB;
}

// Add passenger to appropriate queue based on type and end station
void Station::Addpassenger(Passengers* passenger)
{
    if (passenger->getType() == "WP")
    {
        if (passenger->getEndStation() > stationNumber)
            WPpassengersF.enqueue(passenger);
        else
            WPpassengersB.enqueue(passenger);
    }
    else if (passenger->getType() == "NP")
    {
        if (passenger->getEndStation() > stationNumber)
            NPpassengersF.enqueue(passenger);
        else
            NPpassengersB.enqueue(passenger);
    }
    else if (passenger->getType() == "SP")
    {
        if (passenger->getEndStation() > stationNumber)
            SPpassengersF.enQueue(passenger, passenger->getPriority());
        else
            SPpassengersB.enQueue(passenger, passenger->getPriority());
    }
}

void Station::AddwpBus(Bus* bus)
{
    if (bus->getNextDestination() >= bus->getCurrentDestination()) {

        waitingWBusF.enqueue(bus);
        bus->setDirection("FWD");
    }
    else {
        waitingWBusB.enqueue(bus);
        bus->setDirection("BCK");
    }
}
void Station::AddMBus(Bus* bus)
{
    if (bus->getNextDestination() >= bus->getCurrentDestination()) {
        waitingMBusF.enqueue(bus);
        bus->setDirection("FWD");
    }
    else {
        waitingMBusB.enqueue(bus);
        bus->setDirection("BCK");

    }
}
void Station::AddWPMaintaiance(Bus* bus)
{
    WPMaintainance.enqueue(bus);
}
void Station::AddMMaintaiance(Bus* bus)
{
    MMaintainance.enqueue(bus);
}

//Functions to remove the buses according to their direction
bool Station::RemoveMbusF(Bus* &bus)
{
    return waitingMBusF.dequeue(bus);
}

bool Station::RemoveMbusB(Bus* &bus)
{
    return waitingMBusB.dequeue(bus);
}

bool Station::RemoveWbusF(Bus* &bus)
{
   return waitingWBusF.dequeue(bus);
}

bool Station::RemoveWbusB(Bus* &bus)
{
    return waitingWBusB.dequeue(bus);
}
//End of removing functions

bool Station::RemoveWPMaintainance(Bus* bus)
{
    return WPMaintainance.dequeue(bus);
}
bool Station::RemoveMMaintainance(Bus* bus)
{
    return MMaintainance.dequeue(bus);
}
// Remove passenger from a generic queue using ID
bool Station::removePassengerUsingID(Queue<Passengers*>& p, int id) {
    bool flag = false;

    Queue<Passengers*>temp;
    Passengers* x = nullptr;
    while (!p.isempty()) {
        p.dequeue(x);
        if (x->getID() != id) {
            temp.enqueue(x);
        }
        flag = x->getID() == id;
    }
    while (!temp.isempty()) {
        temp.dequeue(x);
        p.enqueue(x);
    }
    return flag;
}

// Remove special passenger from a priority queue using ID
bool Station::removeSpecialPassengerUsingId(PriorityQueue<Passengers*>& p, int id) {
    bool flag = false;

    PriorityQueue<Passengers*>temp;
    Passengers* x = nullptr;
    while (!p.isEmpty()) {
        p.deQueue(x);
        if (x->getID() != id) {
            temp.enQueue(x, x->getPriority());
        }
        flag = x->getID() == id;
    }
    while (!temp.isEmpty()) {
        temp.deQueue(x);
        p.enQueue(x, x->getPriority());
    }
    return flag;
}


void Station::loadMPassOnBusB()
{

    Passengers* pass;
    Bus* mbus;
    int onTime = 0;
    if ((waitingMBusB.peek(mbus) || (SPpassengersB.peek(pass)|| NPpassengersB.peek(pass)))&& !mbus->isMaintenanceRequired())
    {
        while (mbus->getCurrentCap() < mbus->getMaxCap())
        {
            if (SPpassengersB.peek(pass))
            {
                SPpassengersB.deQueue(pass);
                onTime += pass->getOn_OffTime();
                mbus->load(pass);
                mbus->incrementCurrentCap();
            }
            else if (NPpassengersB.peek(pass))
            {
                NPpassengersB.dequeue(pass);
                onTime += pass->getOn_OffTime();
                mbus->load(pass);
                mbus->incrementCurrentCap();

            }
            else
            {
                break;
            }
            mbus->setIsLoading(true);

            int nextonTime = onTime + pass->getOn_OffTime();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                mbus->setCurrentBusTime(mbus->getCurrentBusTime() + 1);
                return;
            }
            //  wbus->setCurrentBusTime(timer + timeInMin);

        }
        mbus->setIsLoading(false);

    }
}

void Station::unloadWpPassOffBusF(Queue<Passengers*>&finishlist, Time timer)
{
    Passengers* pass;
    Bus* wbus;
    int onTime = 0;
    if (waitingWBusF.peek(wbus))
    {
        while (wbus->getpassengerList().peek(pass) && pass->getEndStation()==stationNumber)
        {
            wbus->getpassengerList().deQueue(pass);//No need to use the unload function inside the bus dequeue from the passengerslist directly

            ArrivedPass.enqueue(pass);
            finishlist.enqueue(pass);
            pass->setFinishedTime(timer);
            pass->setMoveTime(wbus->getBusMoveTime());

            onTime += pass->getOn_OffTime();
            wbus->setIsUnLoading(true);
            int nextonTime = onTime + pass->getOn_OffTime();
            wbus->decrementCurrentCap();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                wbus->setCurrentBusTime(wbus->getCurrentBusTime() + 1);
                return;
            }
        }
        wbus->setIsUnLoading(false);


    }


}
void Station::unloadWpPassOffBusB(Queue<Passengers*>& finishlist, Time timer)
{
    Passengers* pass;
    Bus* wbus;
    int onTime = 0;
    if (waitingWBusB.peek(wbus))
    {
        while (wbus->getpassengerList().peek(pass) && pass->getEndStation() == stationNumber)
        {
            wbus->getpassengerList().deQueue(pass);//No need to use the unload function inside the bus dequeue from the passengerslist directly

            ArrivedPass.enqueue(pass);
            finishlist.enqueue(pass);
            pass->setFinishedTime(timer);
            pass->setMoveTime(wbus->getBusMoveTime());

            onTime += pass->getOn_OffTime();
            wbus->setIsUnLoading(true);
            wbus->decrementCurrentCap();
            int nextonTime = onTime + pass->getOn_OffTime();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                wbus->setCurrentBusTime(wbus->getCurrentBusTime() + 1);

                return;
            }
        }
        wbus->setIsUnLoading(false);

    }


}

void Station::unloadMPassOffBusF(Queue<Passengers*>& finishlist, Time timer)
{
    Passengers* pass;
    Bus* mbus;
    int onTime = 0;
    if (waitingMBusF.peek(mbus))
    {
        while (mbus->getpassengerList().peek(pass) && pass->getEndStation() == stationNumber)
        {
            mbus->getpassengerList().deQueue(pass);//No need to use the unload function inside the bus dequeue from the passengerslist directly

            ArrivedPass.enqueue(pass);
            finishlist.enqueue(pass);
            pass->setFinishedTime(timer);
            pass->setMoveTime(mbus->getBusMoveTime());

            onTime += pass->getOn_OffTime();
            mbus->setIsUnLoading(true);
            mbus->decrementCurrentCap();
            int nextonTime = onTime + pass->getOn_OffTime();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                mbus->setCurrentBusTime(mbus->getCurrentBusTime() + 1);
                return;
            }
        }
        mbus->setIsUnLoading(false);

    }
}
void Station::unloadMPassOffBusB(Queue<Passengers*>& finishlist, Time timer)
{
    Passengers* pass;
    Bus* mbus;
    int onTime = 0;
    if (waitingMBusB.peek(mbus))
    {
        while (mbus->getpassengerList().peek(pass) && pass->getEndStation() == stationNumber )
        {
            mbus->getpassengerList().deQueue(pass);//No need to use the unload function inside the bus dequeue from the passengerslist directly

            ArrivedPass.enqueue(pass);
            finishlist.enqueue(pass);
            pass->setFinishedTime(timer);
            pass->setMoveTime(mbus->getBusMoveTime());

            mbus->setIsUnLoading(true);
            mbus->decrementCurrentCap();
            onTime += pass->getOn_OffTime();
            int nextonTime = onTime + pass->getOn_OffTime();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                mbus->setCurrentBusTime(mbus->getCurrentBusTime() + 1);
                return;
            }
        }
        mbus->setIsUnLoading(false);

    }
}

void Station::incrementAutoPromoted()
{
    this->counterOfAutoPromoted++;
}

int Station::getAutoPromotedCounter()
{
    return this->counterOfAutoPromoted;
}

void Station::autoPromote(PriorityQueue<Passengers*>& special, Queue<Passengers*>& normal, Time timer)
{
    bool flag = true;
    Queue<Passengers*> temp;
    Passengers* ptr = nullptr;
    while (!normal.isempty()) {
        normal.dequeue(ptr);
        if (timer.toTotalMinutes() - ptr->getArrivalTime().toTotalMinutes() >= ptr->getMaxWaitingTime()) {
            ptr->setPriority(1);
            ptr->setType("SP");
            ptr->setSPType("aged");
            special.enQueue(ptr,ptr->getPriority());
            incrementAutoPromoted();
        }
        else {
            temp.enqueue(ptr);
        }
    }

    while (!temp.isempty()) {
        temp.dequeue(ptr);
        normal.enqueue(ptr);
    }


}


void Station::loadMPassOnBusF()
{
    Bus* mbus;
    int onTime = 0;

    // Separate variables for SP and NP passengers
    Passengers* spPass = nullptr;
    Passengers* npPass = nullptr;

    if ((waitingMBusF.peek(mbus) || (SPpassengersF.peek(spPass) || NPpassengersF.peek(npPass)))&&!mbus->isMaintenanceRequired())
    {
        while (mbus->getCurrentCap() < mbus->getMaxCap())
        {
            if (SPpassengersF.peek(spPass))
            {
                SPpassengersF.deQueue(spPass);
                onTime += spPass->getOn_OffTime();
                mbus->load(spPass);
                mbus->incrementCurrentCap();
            }
            else if (NPpassengersF.peek(npPass))
            {
                NPpassengersF.dequeue(npPass);
                onTime += npPass->getOn_OffTime();
                mbus->load(npPass);
                mbus->incrementCurrentCap();
            }
            else
            {
                break;
            }

            mbus->setIsLoading(true);

            int nextOnTime = onTime + (spPass ? spPass->getOn_OffTime() : npPass->getOn_OffTime());
            if (onTime % 60 == 0 || nextOnTime > 60)
            {
                mbus->setCurrentBusTime(mbus->getCurrentBusTime() + 1);
                return;
            }
        }

        mbus->setIsLoading(false);
    }
}

void Station::loadWpPassOnBusF()
{
    Passengers* pass;
    Bus* wbus;
    int onTime = 0;
    if((waitingWBusF.peek(wbus) || WPpassengersF.peek(pass))&& !wbus->isMaintenanceRequired())
    {
         while (wbus->getCurrentCap() < wbus->getMaxCap())
        {
             if (WPpassengersF.peek(pass))
             {
                 WPpassengersF.dequeue(pass);
                 onTime += pass->getOn_OffTime();

                 wbus->load(pass);
                 wbus->incrementCurrentCap();
             }
             else
             {
                 break;
             }
             wbus->setIsLoading(true);


            int nextonTime = onTime + pass->getOn_OffTime();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                wbus->setCurrentBusTime(wbus->getCurrentBusTime() + 1);
                return;
            }
            //  wbus->setCurrentBusTime(timer + timeInMin);

        }
         wbus->setIsLoading(false);

    }


}

void Station::loadWpPassOnBusB()
{
    Passengers* pass;
    Bus* wbus;
    int onTime = 0;
    if ((waitingWBusB.peek(wbus) || WPpassengersB.peek(pass))&& !wbus->isMaintenanceRequired())
    {
        while (wbus->getCurrentCap() < wbus->getMaxCap())
        {
            if (WPpassengersB.peek(pass))
            {
                WPpassengersB.dequeue(pass);
                onTime += pass->getOn_OffTime();
                wbus->load(pass);
                wbus->incrementCurrentCap();
            }
            else
            {
                break;
            }

            wbus->setIsLoading(true);

            int nextonTime = onTime + pass->getOn_OffTime();
            if (onTime % 60 == 0 || nextonTime > 60)//condition for the 1 min  lesa mesh 3aref sa7 wala laa ay habal for now
            {
                wbus->setCurrentBusTime(wbus->getCurrentBusTime() + 1);
                return;
            }
            //  wbus->setCurrentBusTime(timer + timeInMin);

        }
        wbus->setIsLoading(false);

    }
}




// Return total count of normal passengers in both forward and backward queues
int Station::returnTotalNormalCount()
{
    return (this->NPpassengersF.GetSize() + this->NPpassengersB.GetSize());
}

// Return total count of wheelchair passengers in both forward and backward queues
int Station::returnTotalWheelChairCount()
{
    return (this->WPpassengersF.GetSize() + this->WPpassengersB.GetSize());
}

// Return total count of special passengers in both forward and backward queues
int Station::returnTotalSpecialCount()
{
    return (this->SPpassengersF.getCount() + SPpassengersB.getCount());
}

int Station::returnTotalWaitingBusCounts()
{
    return (this->waitingMBusB.GetSize()+this->waitingMBusF.GetSize()+this->waitingWBusB.GetSize()+this->waitingWBusF.GetSize());
}

int Station::returnTotalBusINCheckUp()
{
    return (this->WPMaintainance.GetSize()+this->MMaintainance.GetSize());
}
