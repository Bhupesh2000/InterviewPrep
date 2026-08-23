#ifndef ELEVATOR_STRATEGY_H
#define ELEVATOR_STRATEGY_H

#include <vector>
#include "../controller/ElevatorController.h"

class ElevatorStrategy{
public:
    virtual ~ElevatorStrategy() = default;
    virtual ElevatorController* getElevator(std::vector<ElevatorController*>& controllers, int floorId, Direction d) = 0;
};

#endif