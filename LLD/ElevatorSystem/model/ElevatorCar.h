#ifndef ELEVATOR_CAR_H
#define ELEVATOR_CAR_H

#include "./Door.h"
#include "../enum/DoorStatus.h"
#include "../enum/ElevatorStatus.h"
#include "../enum/MovementDirection.h"

class ElevatorCar{
    int id;
    int currentFloor;
    Door* d;
    ElevatorStatus status;
    MovementDirection direction;

public:
    explicit ElevatorCar(int id){
        this -> id = id;
        currentFloor = 0;
        d = new Door(DoorStatus::CLOSE);
        status = ElevatorStatus::IDLE;
        direction = MovementDirection::NONE;
    }

    ~ElevatorCar(){
        delete d;
    }

    void moveToFoor(int floorId){
        for(int i = 0; i < 100; i++){
            if(i == floorId){
                currentFloor = floorId;
                d -> openDoor();
                for(int j = 0; j < 100000; j++){}
                d -> closeDoor();
                return;
            }
        }
    }

    void setStatus(ElevatorStatus s){
        this -> status = s;
    }

    void setDirection(MovementDirection d){
        this -> direction = d;
    }

    int getId(){
        return id;
    }

    ElevatorStatus getStatus(){
        return status;
    }

    MovementDirection getMovingDirection(){
        return direction;
    }

    int getCurrentFloor(){
        return currentFloor;
    }

};

#endif