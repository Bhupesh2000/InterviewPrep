#ifndef RATE_LIMITER_SERVICE_H
#define RATE_LIMITER_SERVICE_H

#include <string>
#include <unordered_map>
#include "../factory/RateLimiterFactory.h"
#include "../enum/UserTier.h"
#include "../rateLimiter/RateLimiter.h"
#include "../model/RateLimiterConfig.h"
#include "../model/User.h"

class RateLimiterService{
    RateLimiterFactory* factory;
    // The only container that owns limiters. Each limiter owns its own config,
    // so there is no second map to keep in sync.
    std::unordered_map<UserTier, RateLimiter*> rateLimiterTier;
public:
    RateLimiterService(RateLimiterFactory* factory = new RateLimiterFactory()) : factory(factory){};

    ~RateLimiterService(){
        delete factory;
        for(auto& pair : rateLimiterTier) delete pair.second;
    }

    RateLimiterService(const RateLimiterService&) = delete;
    RateLimiterService& operator=(const RateLimiterService&) = delete;

    bool allowRequest(User* user){
        int id = user -> getUserId();
        UserTier tier = user -> getUserTier();

        if(rateLimiterTier.count(tier) == 0) return false;
        return rateLimiterTier[tier]->allowRequest(id);
    }

    // Takes ownership of `config` unconditionally: either the new limiter adopts
    // it, or we free it here.
    void addNewRateLimiter(UserTier tier, std::string algo, RateLimiterConfig* config){
        RateLimiter* rateLimiter = factory -> createRateLimiter(algo, config);

        if(rateLimiter == nullptr){
            // Unknown algorithm — the factory never adopted the config, so it is
            // still ours to free.
            delete config;
            return;
        }

        // operator[] value-initialises a new slot to nullptr, so this deletes the
        // previous limiter (and its config) when a tier is re-registered, and is
        // a harmless no-op the first time.
        RateLimiter*& slot = rateLimiterTier[tier];
        delete slot;
        slot = rateLimiter;
    }
};

#endif
