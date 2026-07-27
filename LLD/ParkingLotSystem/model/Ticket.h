#ifndef TICKET_H
#define TICKET_H

#include <mutex>
#include <string>
#include "../enum/VehicleType.h"
#include "./ParkingSpot.h"

class Ticket{
    inline static int nextId = 1;
    int id;
    std::string vehiclePlateNo;
    VehicleType vehicleType;
    std::string timeOfEntry;
    std::string timeOfExit;
    int floorId;
    ParkingSpot* spot;
    bool active;
    mutable std::mutex mtx;

public:
    Ticket(const std::string& vehiclePlateNo, VehicleType vehicleType, const std::string& timeOfEntry,
           int floorId, ParkingSpot* spot) :
        id(nextId ++), vehiclePlateNo(vehiclePlateNo), vehicleType(vehicleType), timeOfEntry(timeOfEntry),
        timeOfExit(""), floorId(floorId), spot(spot), active(true){};

    int getId() const{
        return id;
    }

    const std::string& getVehiclePlateNo() const{
        return vehiclePlateNo;
    }

    // The exit gate needs this to hand the spot back to the manager that owns
    // it, rather than releasing the spot behind the manager's back.
    VehicleType getVehicleType() const{
        return vehicleType;
    }

    const std::string& getTimeOfEntry() const{
        return timeOfEntry;
    }

    bool isActive() const{
        std::lock_guard<std::mutex> lock(mtx);
        return active;
    }

    // Atomic test and clear, exactly one caller gets true for a given ticket.
    // Checking isActive() and then deactivating as two steps would let two
    // threads both run the exit flow for the same vehicle.
    bool tryDeactivate(){
        std::lock_guard<std::mutex> lock(mtx);
        if(!active) return false;
        active = false;
        return true;
    }

    void setTimeOfExit(const std::string& time){
        std::lock_guard<std::mutex> lock(mtx);
        timeOfExit = time;
    }

    std::string getTimeOfExit() const{
        std::lock_guard<std::mutex> lock(mtx);
        return timeOfExit;
    }

    int getFloorId() const{
        return floorId;
    }

    ParkingSpot* getParkingSpot() const{
        return spot;
    }
};

#endif
