#ifndef RATE_LIMITER_CONFIG_H
#define RATE_LIMITER_CONFIG_H

class RateLimiterConfig{
    int maxRequests;
    int windowInSeconds;

public:
    RateLimiterConfig(int maxRequests, int windowInSeconds) : maxRequests(maxRequests), windowInSeconds(windowInSeconds){};

    int getMaxRequests() const{
        return maxRequests;
    }

    int getWindowInSeconds() const{
        return windowInSeconds;
    }
};

#endif
