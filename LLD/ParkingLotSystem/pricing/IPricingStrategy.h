#ifndef I_PRICING_STRATEGY_H
#define I_PRICING_STRATEGY_H

#include "../model/Ticket.h"

class IPricingStrategy{
public:
    IPricingStrategy() = default;
    virtual ~IPricingStrategy() = default;
    virtual int calculatePrice(Ticket* ticket) = 0;
};

#endif