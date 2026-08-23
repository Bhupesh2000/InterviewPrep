#ifndef INTERNAL_BUTTON_H
#define INTERNAL_BUTTON_H

#include "../controller/ElevatorController.h"

class InternalButton{
    ElevatorController* controller;

public:
    InternalButton(ElevatorController* cntrl) : controller(cntrl){};

    void pressButton(int floorId){
        controller -> submitRequestInternal(floorId);
    }
};

#endif