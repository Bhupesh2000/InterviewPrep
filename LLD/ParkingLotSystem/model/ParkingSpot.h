#ifndef PARKING_SPOT_H
#define PARKING_SPOT_H

#include "../enum/VehicleType.h"

class ParkingSpot{
    int id;
    bool isFree;
    VehicleType type;

public:
    ParkingSpot(int id, VehicleType type) : id(id), isFree(true), type(type){};

    int getId() const{
        return id;
    }

    VehicleType getVehicleType() const{
        return type;
    }

    bool isSpotFree() const{
        return isFree;
    }

    void allocate(){
        isFree = false;
    }

    void release(){
        isFree = true;
    }
};


#endif