#ifndef DOOR_H
#define DOOR_H

#include "../enum/DoorStatus.h"

class Door{
    DoorStatus status;

public:
    Door(DoorStatus initialStatus) : status(initialStatus){};

    void openDoor(){
        status = DoorStatus::OPEN;
    }

    void closeDoor(){
        status = DoorStatus::CLOSE;
    }
};

#endif