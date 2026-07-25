#ifndef RATE_LIMITER_FACTORY_H
#define RATE_LIMITER_FACTORY_H

#include <string>
#include "../model/RateLimiterConfig.h"
#include "../rateLimiter/RateLimiter.h"
#include "../rateLimiter/TokenBucketRateLimiter.h"
#include "../rateLimiter/FixedWindowRateLimiter.h"

class RateLimiterFactory{
public:
    // On success the returned limiter owns `config`. On failure (unknown algo)
    // ownership stays with the caller, who must free it.
    RateLimiter* createRateLimiter(std::string algo, RateLimiterConfig* config){
        if(algo == "token_bucket") return new TokenBucketRateLimiter(config);
        else if(algo == "fixed_window") return new FixedWindowRateLimiter(config);
        else return nullptr;
    }
};

#endif