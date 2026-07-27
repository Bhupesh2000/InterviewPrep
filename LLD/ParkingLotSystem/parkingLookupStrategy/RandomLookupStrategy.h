#ifndef RANDOM_LOOKUP_PARKING_STRATEGY
#define RANDOM_LOOKUP_PARKING_STRATEGY

#include "./IParkingLookupStrategy.h"

class RandomLookupStrategy : public IParkingLookupStrategy{
public:
    ParkingSpot* findSpot(std::vector<ParkingSpot*>& parkingSpotsList) override{
        for(auto it : parkingSpotsList){
            if(it -> isSpotFree()){
                return it;
            }
        }
        return nullptr;
    }
};

#endif