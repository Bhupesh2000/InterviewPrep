#ifndef PARKING_BUILDING_H
#define PARKING_BUILDING_H

#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>
#include "../enum/VehicleType.h"
#include "./ParkingLevel.h"

class ParkingBuilding{
    std::unordered_map<int, ParkingLevel*> levels;
    mutable std::mutex mtx;

    // Copy of the level pointers, taken under the lock so the map can be
    // iterated without holding it while parking.
    std::vector<std::pair<int, ParkingLevel*>> snapshotLevels() const{
        std::lock_guard<std::mutex> lock(mtx);
        return std::vector<std::pair<int, ParkingLevel*>>(levels.begin(), levels.end());
    }

    ParkingLevel* getLevel(int levelId) const{
        std::lock_guard<std::mutex> lock(mtx);
        auto it = levels.find(levelId);
        return it == levels.end() ? nullptr : it -> second;
    }

public:
    ParkingBuilding() = default;
    ~ParkingBuilding(){
        for(auto it : levels){
            delete it.second;
        }
    }

    void addLevel(int levelId, ParkingLevel* level){
        std::lock_guard<std::mutex> lock(mtx);
        levels[levelId] = level;
    }

    // Tries each level in turn and returns {-1, nullptr} when none can take the
    // vehicle. There is deliberately no hasAvailability() check first, asking
    // and then parking leaves a window for another thread to take the spot.
    std::pair<int, ParkingSpot*> park(VehicleType type){
        for(auto& it : snapshotLevels()){
            ParkingSpot* spot = it.second -> park(type);
            if(spot != nullptr){
                return std::make_pair(it.first, spot);
            }
        }
        return std::make_pair(-1, nullptr);
    }

    void unpark(int levelId, VehicleType type, ParkingSpot* spot){
        ParkingLevel* level = getLevel(levelId);
        if(level != nullptr){
            level -> unpark(type, spot);
        }
    }
};

#endif
