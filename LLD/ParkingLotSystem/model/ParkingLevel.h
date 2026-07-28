#ifndef PARKING_LEVEL_H
#define PARKING_LEVEL_H

#include <unordered_map>
#include <mutex>
#include "../enum/VehicleType.h"
#include "../manager/ParkingSpotManager.h"

class ParkingLevel{
    int id;
    std::unordered_map<VehicleType, ParkingSpotManager*> parkingSpotManagersMap;
    mutable std::mutex mtx;

    // The lock here guards the map only. The manager pointer is looked up and
    // the lock released before calling into it, so no lock is ever held while
    // acquiring another one.
    ParkingSpotManager* getManager(VehicleType type) const{
        std::lock_guard<std::mutex> lock(mtx);
        auto it = parkingSpotManagersMap.find(type);
        return it == parkingSpotManagersMap.end() ? nullptr : it -> second;
    }

public:
    ParkingLevel(int id) : id(id){};

    ~ParkingLevel(){
        for(auto it : parkingSpotManagersMap){
            delete it.second;
        }
    }

    int getId() const{
        return id;
    }

    void addParkingSpotManager(VehicleType type, ParkingSpotManager* parkingSpotManager){
        std::lock_guard<std::mutex> lock(mtx);
        parkingSpotManagersMap[type] = parkingSpotManager;
    }

    bool hasAvailability(VehicleType type) const{
        ParkingSpotManager* parkingSpotManager = getManager(type);
        return parkingSpotManager != nullptr && parkingSpotManager -> hasFreeSpot();
    }

    // Returns nullptr when this level cannot take the vehicle.
    ParkingSpot* park(VehicleType type){
        ParkingSpotManager* parkingSpotManager = getManager(type);
        return parkingSpotManager == nullptr ? nullptr : parkingSpotManager -> park();
    }

    void unpark(VehicleType type, ParkingSpot* spot){
        ParkingSpotManager* parkingSpotManager = getManager(type);
        if(parkingSpotManager != nullptr){
            parkingSpotManager -> unpark(spot);
        }
    }
};

#endif
