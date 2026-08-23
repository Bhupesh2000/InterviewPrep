#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include <set>
#include <unordered_set>
#include <vector>
#include <mutex>
#include "../enum/Direction.h"
#include "../enum/MovementDirection.h"
#include "../enum/ElevatorStatus.h"
#include "../model/ElevatorCar.h"

class ElevatorController{
    int id;
    ElevatorCar* elevator;
    std::set<int> upFloors;
    std::set<int, std::greater<int>> downFloors;
    std::unordered_set<int> remainingFloors;
    bool isRunning;
    std::mutex mtx;

    void controlElevator(){
        {
            std::lock_guard<std::mutex> lock(mtx);

            if(isRunning){return;}

            if(upFloors.empty() && downFloors.empty() && remainingFloors.empty()){
                return;
            }

            isRunning = true;
            elevator->setStatus(ElevatorStatus::MOVING);

            // Decide initial direction.
            if(elevator->getMovingDirection() == MovementDirection::NONE){
                if(!upFloors.empty()){
                    elevator->setDirection(MovementDirection::UP);
                }
                else{
                    elevator->setDirection(MovementDirection::DOWN);
                }
            }
        }

        while (isRunning)
        {
            MovementDirection movDir;
            int nextFloor = -1;

            {
                std::lock_guard<std::mutex> lock(mtx);

                movDir = elevator->getMovingDirection();

                if(movDir == MovementDirection::UP){

                    if(!upFloors.empty()){
                        nextFloor = *upFloors.begin();
                    }
                    else{
                        // UP requests are exhausted.
                        // Move remaining requests into UP.
                        for(int floor : remainingFloors){
                            upFloors.insert(floor);
                        }

                        remainingFloors.clear();

                        elevator->setDirection(MovementDirection::DOWN);
                    }
                }

                else if(movDir == MovementDirection::DOWN){

                    if(!downFloors.empty()){
                        nextFloor = *downFloors.begin();
                    }
                    else{
                        // DOWN requests are exhausted.
                        // Move remaining requests into DOWN.
                        for(int floor : remainingFloors){
                            downFloors.insert(floor);
                        }

                        remainingFloors.clear();

                        elevator->setDirection(MovementDirection::UP);
                    }
                }
            }

            // We have a floor to visit.
            if(nextFloor != -1){

                // DON'T hold mtx while elevator is moving.
                elevator->moveToFoor(nextFloor);

                {
                    std::lock_guard<std::mutex> lock(mtx);

                    if(movDir == MovementDirection::UP){
                        upFloors.erase(nextFloor);
                    }
                    else{
                        downFloors.erase(nextFloor);
                    }
                }

                continue;
            }

            // No floor was selected. Check if we're done.
            {
                std::lock_guard<std::mutex> lock(mtx);

                if(upFloors.empty() && downFloors.empty() && remainingFloors.empty()){

                    elevator->setDirection(MovementDirection::NONE);
                    elevator->setStatus(ElevatorStatus::IDLE);
                    isRunning = false;
                }
            }
        }
        
    }

public:
    ElevatorController(int id) : id(id), elevator(new ElevatorCar(id)), isRunning(false){};
    ~ElevatorController(){
        delete elevator;
    }

    void submitRequestInternal(int floorId){
        {
            std::lock_guard<std::mutex> lock(mtx);
            int currentFloor = elevator -> getCurrentFloor();
            if(currentFloor == floorId) return;
            else if(floorId > currentFloor) upFloors.insert(floorId);
            else downFloors.insert(floorId);
        }
        controlElevator();
    }

    void submitRequestExternal(int floorId, Direction d){
        {
            std::lock_guard<std::mutex> lock(mtx);
            int currentFloor = elevator -> getCurrentFloor();
            if(currentFloor == floorId) return;
            MovementDirection movDir = elevator -> getMovingDirection();

            if(movDir == MovementDirection::UP){
                if(d == Direction::UP){
                    if(floorId > currentFloor) upFloors.insert(floorId);
                    else remainingFloors.insert(floorId);
                }
                else downFloors.insert(floorId);
            }
            
            else if(movDir == MovementDirection::DOWN){
                if(d == Direction::DOWN){
                    if(floorId < currentFloor) downFloors.insert(floorId);
                    else remainingFloors.insert(floorId);
                }
                else upFloors.insert(floorId);
            }

            else{
                if(floorId > currentFloor) upFloors.insert(floorId);
                else downFloors.insert(floorId);
            }
        }
        controlElevator();
        
    }

    int getTotalTasks(){
        std::lock_guard<std::mutex> lock(mtx);
        return upFloors.size() + downFloors.size() + remainingFloors.size();
    }

    int getId(){
        return id;
    }
};

#endif