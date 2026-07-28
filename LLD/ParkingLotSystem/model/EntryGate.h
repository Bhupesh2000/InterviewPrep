#ifndef ENTRY_GATE_H
#define ENTRY_GATE_H

#include "./ParkingBuilding.h"
#include "./Ticket.h"
#include "./Vehicle.h"

class EntryGate{
    ParkingBuilding* building;

public:
    EntryGate(ParkingBuilding* building) : building(building){};

    Ticket* allocateSlot(Vehicle* vehicle){
        Ticket* ticket = nullptr;
        VehicleType type = vehicle -> getVehicleType();
        std::pair<int, ParkingSpot*> spot = building -> park(type);
        if(spot.second != nullptr){
            std::string timeOfEntry = "01:01:2026 01:01:01";
            ticket = new Ticket(vehicle -> getPlateNo(), type, timeOfEntry, spot.first, spot.second);
        }
        return ticket;
    }
};

#endif