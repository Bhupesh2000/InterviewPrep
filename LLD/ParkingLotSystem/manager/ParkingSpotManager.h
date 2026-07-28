#ifndef PARKING_SPOT_MANAGER_H
#define PARKING_SPOT_MANAGER_H

#include <mutex>
#include <vector>
#include "../model/ParkingSpot.h"
#include "../parkingLookupStrategy/IParkingLookupStrategy.h"
#include "../parkingLookupStrategy/RandomLookupStrategy.h"

// Owns the spots of one vehicle type on one level, and is the only place that
// mutates a spot's free flag. Every read and write of that flag goes through
// this mutex, so picking a spot and claiming it cannot interleave.
class ParkingSpotManager{
    std::vector<ParkingSpot*> parkingSpots;
    IParkingLookupStrategy* parkingStrategy;
    mutable std::mutex mtx;

public:
    ParkingSpotManager(IParkingLookupStrategy* parkingStrategy) : parkingStrategy(parkingStrategy){};
    ~ParkingSpotManager(){
        for(auto it : parkingSpots) delete it;
        delete parkingStrategy;
    }

    void addParkingSpot(ParkingSpot* spot){
        std::lock_guard<std::mutex> lock(mtx);
        parkingSpots.push_back(spot);
    }

    // Point in time query. Callers must not use it to decide that a later
    // park() will succeed, park() reports that atomically itself.
    bool hasFreeSpot() const{
        std::lock_guard<std::mutex> lock(mtx);
        for(auto it : parkingSpots){
            if(it -> isSpotFree()) return true;
        }
        return false;
    }

    // Returns nullptr when every spot is taken.
    ParkingSpot* park(){
        std::lock_guard<std::mutex> lock(mtx);
        ParkingSpot* spot = parkingStrategy -> findSpot(parkingSpots);
        if(spot == nullptr) return nullptr;
        spot -> allocate();
        return spot;
    }

    void unpark(ParkingSpot* spot){
        if(spot == nullptr) return;
        std::lock_guard<std::mutex> lock(mtx);
        spot -> release();
    }
};

#endif
