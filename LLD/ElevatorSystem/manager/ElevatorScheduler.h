#ifndef ELEVATOR_SCHEDULER_H
#define ELEVATOR_SCHEDULER_H

#include <vector>
#include "../enum/Direction.h"
#include "../controller/ElevatorController.h"
#include "../strategy/ElevatorStrategy.h"
#include "../strategy/LeastBusyStrategy.h"

class ElevatorScheduler{
    std::vector<ElevatorController*> controllersList;
    ElevatorStrategy* startegy;

public:
    ElevatorScheduler(std::vector<ElevatorController*> controllers, ElevatorStrategy* startegy) : controllersList(controllers), startegy(startegy){};

    void scheduleElevator(int floorId, Direction d){
        ElevatorController* controller = startegy -> getElevator(controllersList, floorId, d);
        controller -> submitRequestExternal(floorId, d);
    }

    void setStrategy(ElevatorStrategy* startegy){
        this -> startegy = startegy;
    }
};

#endif