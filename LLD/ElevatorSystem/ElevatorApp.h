#ifndef ELEVATOR_APP_H
#define ELEVATOR_APP_H

#include <vector>

#include "./model/Building.h"
#include "./model/ExternalButton.h"
#include "./model/InternalButton.h"
#include "./controller/ElevatorController.h"
#include "./manager/ElevatorScheduler.h"
#include "./dispatcher/ExternalButtonDispatcher.h"
#include "./strategy/ElevatorStrategy.h"
#include "./strategy/LeastBusyStrategy.h"

class ElevatorApp{
    Building* building;

    std::vector<ElevatorController*> controllers;

    ElevatorStrategy* strategy;
    ElevatorScheduler* scheduler;
    ExternalButtonDispatcher* dispatcher;

    std::vector<ExternalButton*> externalButtons;
    std::vector<std::vector<InternalButton*>> internalButtons;

public:
    ElevatorApp(int numberOfFloors, int numberOfElevators){

        building = new Building(numberOfFloors);

        // Create elevator controllers.
        for(int i = 0; i < numberOfElevators; i++){
            controllers.push_back(new ElevatorController(i));
        }

        // Create scheduling components.
        strategy = new LeastBusyStrategy();
        scheduler = new ElevatorScheduler(controllers, strategy);
        dispatcher = new ExternalButtonDispatcher(scheduler);

        // Create external buttons.
        for(int floor = 0; floor <= numberOfFloors; floor++){

            externalButtons.push_back(
                new ExternalButton(floor, Direction::UP, dispatcher)
            );

            externalButtons.push_back(
                new ExternalButton(floor, Direction::DOWN, dispatcher)
            );
        }

        // Create internal buttons.
        for(ElevatorController* controller : controllers){

            std::vector<InternalButton*> buttons;

            for(int floor = 0; floor <= numberOfFloors; floor++){
                buttons.push_back(
                    new InternalButton(controller)
                );
            }

            internalButtons.push_back(buttons);
        }
    }

    ~ElevatorApp(){

        for(ExternalButton* button : externalButtons){
            delete button;
        }

        for(std::vector<InternalButton*>& buttons : internalButtons){
            for(InternalButton* button : buttons){
                delete button;
            }
        }

        delete dispatcher;
        delete scheduler;
        delete strategy;

        for(ElevatorController* controller : controllers){
            delete controller;
        }

        delete building;
    }

    void pressExternalButton(int floorId, Direction direction){

        int index = floorId * 2;

        if(direction == Direction::UP){
            externalButtons[index]->pressButton();
        }
        else{
            externalButtons[index + 1]->pressButton();
        }
    }

    void pressInternalButton(int elevatorId, int floorId){
        internalButtons[elevatorId][floorId]->pressButton(floorId);
    }
};

#endif