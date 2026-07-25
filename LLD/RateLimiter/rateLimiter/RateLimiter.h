#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H

#include "../model/RateLimiterConfig.h"

class RateLimiter{
protected:
    // The limiter is the sole owner of its config and frees it below. No other
    // container keeps a pointer to it, so there is exactly one owner and
    // exactly one delete.
    RateLimiterConfig* config;

public:
    RateLimiter(RateLimiterConfig* config) : config(config){};

    virtual ~RateLimiter(){
        delete config;
    }

    // Sole ownership of a raw pointer: copying would double-free the config.
    RateLimiter(const RateLimiter&) = delete;
    RateLimiter& operator=(const RateLimiter&) = delete;

    virtual bool allowRequest(int userId) = 0;
};

#endif
