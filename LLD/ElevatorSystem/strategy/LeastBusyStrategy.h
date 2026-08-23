#ifndef LEAST_BUSY_STRATEGY_H
#define LEAST_BUSY_STRATEGY_H

#include <vector>
#include <mutex>
#include <climits>
#include "./ElevatorStrategy.h"
#include "../controller/ElevatorController.h"

class LeastBusyStrategy : public ElevatorStrategy{
    std::mutex mtx;
public:
    ElevatorController* getElevator(std::vector<ElevatorController*>& controllers, int, Direction) override{
        if(controllers.size() == 0) return nullptr;
        std::vector<int> tasks;
        {
            std::lock_guard<std::mutex>lock(mtx);
            for(auto cntrl : controllers){
                tasks.push_back(cntrl -> getTotalTasks());
            }
        }

        int minTasks = INT_MAX;
        ElevatorController* cntrl = nullptr;

        for(size_t i = 0; i < tasks.size(); i++){
            if(cntrl == nullptr){
                minTasks = tasks[i];
                cntrl = controllers[i];
            }
            else if(tasks[i] < minTasks){
                minTasks = tasks[i];
                cntrl = controllers[i];
            }
        }

        return cntrl;

    }
};

#endif