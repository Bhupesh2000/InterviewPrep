#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "./ParkingBuilding.h"
#include "./EntryGate.h"
#include "./ExitGate.h"

class ParkingLot{
    ParkingBuilding* building;
    EntryGate* entryGate;
    ExitGate* exitGate;

public:
    ParkingLot(ParkingBuilding* building, CostComputation* costComputation) :
        building(building), entryGate(new EntryGate(building)), exitGate(new ExitGate(building, costComputation)){};

    ~ParkingLot(){
        delete entryGate;
        delete exitGate;
        delete building;
    }

    Ticket* allocateSlot(Vehicle* vehicle){
        return entryGate -> allocateSlot(vehicle);
    }

    void exit(Ticket* ticket, IPaymentStrategy* paymentStrategy){
        exitGate -> exit(ticket, paymentStrategy);
    }
};

#endif