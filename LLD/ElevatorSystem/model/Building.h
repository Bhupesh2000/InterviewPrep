#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "./Floor.h"

class Building{
    std::vector<Floor*> floors;

public:
    Building(int n){
        for(int i = 0; i <= n; i++){
            floors.push_back(new Floor(i));
        }
    }

    ~Building(){
        for(Floor* f : floors) delete f;
    }

    Floor* getFloor(int n){
        return floors[n];
    }
};

#endif