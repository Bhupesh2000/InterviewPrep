#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "../enum/VehicleType.h"

class Vehicle{
    std::string plateNo;
    VehicleType type;

public:
    Vehicle(const std::string& plateNo, VehicleType type) : plateNo(plateNo), type(type){};

    ~Vehicle() = default;

    const std::string& getPlateNo() const{
        return plateNo;
    }

    VehicleType getVehicleType() const{
        return type;
    }
};

#endif