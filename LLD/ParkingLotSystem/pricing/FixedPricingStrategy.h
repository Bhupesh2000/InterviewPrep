#ifndef FIXED_PRICING_STRATEGY_H
#define FIXED_PRICING_STRATEGY_H 

#include "./IPricingStrategy.h"

class FixedPricingStrategy : public IPricingStrategy{
public:
    int calculatePrice(Ticket* ticket) override{
        return 100;
    }
};

#endif