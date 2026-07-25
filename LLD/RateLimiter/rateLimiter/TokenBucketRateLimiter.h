#ifndef TOKEN_BUCKET_RATE_LIMITER_H
#define TOKEN_BUCKET_RATE_LIMITER_H

#include <unordered_map>
#include <mutex>
#include <chrono>
#include <algorithm>
#include "./RateLimiter.h"

class TokenBucketRateLimiter : public RateLimiter{
    struct usersTokenData{
        long long tokens;
        long long lastRefillTime;
    };
    std::unordered_map<int, usersTokenData> userToken;
    std::mutex mtx;

    // steady_clock, not system_clock: this is elapsed-time math, and it must not
    // jump when NTP or the user moves the wall clock. (Fixed window is the other
    // way round — it needs epoch-aligned wall time.)
    long long nowMs() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count();
    }

    // Milliseconds of elapsed time that earn one token, e.g. a 60s window with
    // 10 requests => one token every 6000ms. Clamped to >= 1 so the division in
    // refill() is always safe.
    long long refillIntervalMs() const {
        long long windowMs = static_cast<long long>(config -> getWindowInSeconds()) * 1000LL;
        long long maxRequests = std::max(1, config -> getMaxRequests());
        return std::max<long long>(1, windowMs / maxRequests);
    }

    // Credits whole tokens for the time that has passed and returns the bucket.
    usersTokenData& refill(int userId, long long now) {
        auto it = userToken.find(userId);

        // First time we see a user: full bucket, clock starts now.
        if(it == userToken.end()){
            usersTokenData data;
            data.tokens = config -> getMaxRequests();
            data.lastRefillTime = now;
            return userToken.emplace(userId, data).first -> second;
        }

        usersTokenData& data = it -> second;
        const long long intervalMs = refillIntervalMs();
        long long newTokens = (now - data.lastRefillTime) / intervalMs;

        if(newTokens > 0){
            data.tokens = std::min<long long>(config -> getMaxRequests(), data.tokens + newTokens);
            // Advance by exactly what we paid out rather than resetting to `now`,
            // so the leftover fraction of an interval carries into the next call.
            // Resetting here is what silently throttles a bucket below its
            // configured rate.
            data.lastRefillTime += newTokens * intervalMs;
        }
        return data;
    }

public:
    TokenBucketRateLimiter(RateLimiterConfig* config) : RateLimiter(config){};

    bool allowRequest(int userId) override{
        std::lock_guard<std::mutex> lock(mtx);

        usersTokenData& data = refill(userId, nowMs());

        if(data.tokens > 0){
            data.tokens--;
            return true;
        }
        return false;
    }
};

#endif
