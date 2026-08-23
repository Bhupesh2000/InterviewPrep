#ifndef EXTERNAL_BUTTON_H
#define EXTERNAL_BUTTON_H

#include "../enum/Direction.h"
#include "../dispatcher/ExternalButtonDispatcher.h"

class ExternalButton{
    int floorId;
    Direction direction;
    ExternalButtonDispatcher* dispatcher;

public:
    ExternalButton(int floorId, Direction direction, ExternalButtonDispatcher* dispatcher) : floorId(floorId), direction(direction), dispatcher(dispatcher){};

    void pressButton(){
        dispatcher -> submitRequest(floorId, direction);
    }
};

#endif