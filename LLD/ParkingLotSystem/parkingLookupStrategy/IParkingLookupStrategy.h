#ifndef I_PRAKING_LOOKUP_STRATEGY_H
#define I_PRAKING_LOOKUP_STRATEGY_H

#include <vector>
#include "../model/ParkingSpot.h"

class IParkingLookupStrategy{
public:
    virtual ParkingSpot* findSpot(std::vector<ParkingSpot*>& parkingSpotsList) = 0;
    virtual ~IParkingLookupStrategy() = default;
};

#endif