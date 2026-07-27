#ifndef COST_COMPUTATION_H
#define COST_COMPUTATION_H

#include "./IPricingStrategy.h"
#include "./FixedPricingStrategy.h"

class CostComputation{
    IPricingStrategy* strategy;

public:
    CostComputation(IPricingStrategy* strategy) : strategy(strategy){};
    ~CostComputation(){
        delete strategy;
    }

    int calculateParkingFair(Ticket* ticket){
        return strategy -> calculatePrice(ticket);
    }
};

#endif