#ifndef EXTERNAL_BUTTON_DISPATCHER_H
#define EXTERNAL_BUTTON_DISPATCHER_H

#include "../enum/Direction.h"
#include "../manager/ElevatorScheduler.h"

class ExternalButtonDispatcher{
    ElevatorScheduler* scheduler;
public:
    explicit ExternalButtonDispatcher(ElevatorScheduler* scheduler) : scheduler(scheduler){};
    void submitRequest(int floorId, Direction d){
        scheduler -> scheduleElevator(floorId, d);
    }
};

#endif