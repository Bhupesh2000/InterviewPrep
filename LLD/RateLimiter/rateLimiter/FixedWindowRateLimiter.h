#ifndef FIXED_WINDOW_RATE_LIMITER_H
#define FIXED_WINDOW_RATE_LIMITER_H

#include <unordered_map>
#include <mutex>
#include <chrono>
#include "./RateLimiter.h"

class FixedWindowRateLimiter : public RateLimiter{

    struct userWindowData{
        int requestcount;
        long long windowStart;
    };

    std::unordered_map<int, userWindowData> userCounter;
    std::mutex mtx;

    long long nowSeconds() const{
        return (std::chrono::duration_cast<std::chrono::seconds>
            (std::chrono::system_clock::now().time_since_epoch())
        ).count();
    }

public:

    FixedWindowRateLimiter(RateLimiterConfig* config) : RateLimiter(config){};

    bool allowRequest(int userId) override{
        std::lock_guard<std::mutex> lock(mtx);

        long long now = nowSeconds();
        long long currentWindow = now / config -> getWindowInSeconds();

        if(userCounter.count(userId) != 0){
            userWindowData& userWindow = userCounter[userId];
            long long window = userWindow.windowStart;
            if(window != currentWindow){
                userWindow.windowStart = currentWindow;
                userWindow.requestcount = 1;
                return true;
            }
            else{
                int totalRequestsInWindow = userWindow.requestcount;
                if(totalRequestsInWindow >= config -> getMaxRequests()) return false;
                userWindow.requestcount ++;
                return true;
            }
        }
        else{
            userWindowData userWindow;
            userWindow.requestcount = 1;
            userWindow.windowStart = currentWindow;
            userCounter[userId] = userWindow;
            return true;
        }
    }
};

#endif