#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include "./service/RateLimiterService.h"

static int testsRun = 0;
static int testsFailed = 0;

void check(const std::string& what, bool actual, bool expected){
    testsRun++;
    bool ok = (actual == expected);
    if(!ok) testsFailed++;
    std::cout << (ok ? "  [PASS] " : "  [FAIL] ") << what
              << " -> expected " << (expected ? "ALLOW" : "DENY")
              << ", got " << (actual ? "ALLOW" : "DENY") << "\n";
}

void checkEquals(const std::string& what, int actual, int expected){
    testsRun++;
    bool ok = (actual == expected);
    if(!ok) testsFailed++;
    std::cout << (ok ? "  [PASS] " : "  [FAIL] ") << what
              << " -> expected " << expected << ", got " << actual << "\n";
}

void checkInRange(const std::string& what, int actual, int low, int high){
    testsRun++;
    bool ok = (actual >= low && actual <= high);
    if(!ok) testsFailed++;
    std::cout << (ok ? "  [PASS] " : "  [FAIL] ") << what
              << " -> expected " << low << ".." << high << ", got " << actual << "\n";
}

void sleepSeconds(double s){
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(s * 1000)));
}

// Fixed windows are aligned to the epoch (now / windowInSeconds), so a test that
// starts mid-window can see the window roll over halfway through. Park at a
// boundary first to make the counts deterministic.
void waitForWindowBoundary(int windowInSeconds){
    while(true){
        long long nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        long long offsetMs = nowMs % (windowInSeconds * 1000LL);
        if(offsetMs < 100) return;
        sleepSeconds((windowInSeconds * 1000LL - offsetMs) / 1000.0);
    }
}

// ---------------------------------------------------------------------------

void testFixedWindow(){
    std::cout << "\n== Fixed window: 3 requests / 2 seconds (FREE) ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(3, 2));

    User alice(1, UserTier::FREE);

    waitForWindowBoundary(2);

    check("request 1", service.allowRequest(&alice), true);
    check("request 2", service.allowRequest(&alice), true);
    check("request 3", service.allowRequest(&alice), true);
    check("request 4 (over quota)", service.allowRequest(&alice), false);
    check("request 5 (over quota)", service.allowRequest(&alice), false);

    std::cout << "  ... sleeping past the window boundary ...\n";
    sleepSeconds(2.1);

    check("request after window reset", service.allowRequest(&alice), true);
    check("second request in new window", service.allowRequest(&alice), true);
}

void testFixedWindowIsolatesUsers(){
    std::cout << "\n== Fixed window: quota is per-user, not global ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(2, 60));

    User alice(1, UserTier::FREE);
    User bob(2, UserTier::FREE);

    check("alice 1", service.allowRequest(&alice), true);
    check("alice 2", service.allowRequest(&alice), true);
    check("alice 3 (exhausted)", service.allowRequest(&alice), false);

    check("bob 1 (unaffected by alice)", service.allowRequest(&bob), true);
    check("bob 2", service.allowRequest(&bob), true);
    check("bob 3 (exhausted)", service.allowRequest(&bob), false);
}

void testTokenBucket(){
    std::cout << "\n== Token bucket: 4 tokens / 4 seconds => 1 token per second (PREMIUM) ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::PREMIUM, "token_bucket", new RateLimiterConfig(4, 4));

    User carol(3, UserTier::PREMIUM);

    // A fresh bucket starts full, so the whole burst should go through.
    check("burst 1", service.allowRequest(&carol), true);
    check("burst 2", service.allowRequest(&carol), true);
    check("burst 3", service.allowRequest(&carol), true);
    check("burst 4", service.allowRequest(&carol), true);
    check("burst 5 (bucket empty)", service.allowRequest(&carol), false);

    std::cout << "  ... sleeping 2.2s, expecting ~2 tokens back ...\n";
    sleepSeconds(2.2);

    check("refilled token 1", service.allowRequest(&carol), true);
    check("refilled token 2", service.allowRequest(&carol), true);
    check("no third token yet", service.allowRequest(&carol), false);
}

void testTokenBucketDoesNotOverfill(){
    std::cout << "\n== Token bucket: refill is capped at bucket capacity ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::PREMIUM, "token_bucket", new RateLimiterConfig(2, 1));

    User dave(4, UserTier::PREMIUM);

    check("drain 1", service.allowRequest(&dave), true);
    check("drain 2", service.allowRequest(&dave), true);
    check("empty", service.allowRequest(&dave), false);

    std::cout << "  ... idling 3s (enough for 6 tokens, capacity is 2) ...\n";
    sleepSeconds(3.0);

    check("capped 1", service.allowRequest(&dave), true);
    check("capped 2", service.allowRequest(&dave), true);
    check("capped 3 (capacity was 2, not 6)", service.allowRequest(&dave), false);
}

// Regression test for the sustained-rate bug: polling faster than the refill
// interval used to lose the sub-interval remainder on every call, so the bucket
// delivered roughly half its configured rate. 9 seconds at 1 token/sec must hand
// out ~9 tokens no matter how often we ask.
void testTokenBucketSustainedRate(){
    std::cout << "\n== Token bucket: sustained rate survives polling faster than the refill interval ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::PREMIUM, "token_bucket", new RateLimiterConfig(5, 5));

    User erin(5, UserTier::PREMIUM);

    for(int i = 0; i < 5; i++) service.allowRequest(&erin);   // drain the initial burst
    check("bucket is drained", service.allowRequest(&erin), false);

    std::cout << "  ... polling every 900ms for 9s ...\n";
    int allowed = 0;
    for(int i = 0; i < 10; i++){
        sleepSeconds(0.9);
        if(service.allowRequest(&erin)) allowed++;
    }

    checkInRange("tokens delivered over 9s at 1 token/sec", allowed, 8, 10);
}

void testReRegisteringATierReplacesTheLimiter(){
    std::cout << "\n== Re-registering a tier swaps the limiter (and frees the old one) ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(1, 60));
    // Overwrites the previous limiter and its config; must not leak either.
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(3, 60));

    User frank(6, UserTier::FREE);

    check("request 1 under the new quota", service.allowRequest(&frank), true);
    check("request 2 under the new quota", service.allowRequest(&frank), true);
    check("request 3 under the new quota", service.allowRequest(&frank), true);
    check("request 4 (new quota is 3)", service.allowRequest(&frank), false);
}

void testTiersAreIndependent(){
    std::cout << "\n== Different tiers get different limiters ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(1, 60));
    service.addNewRateLimiter(UserTier::PREMIUM, "token_bucket", new RateLimiterConfig(5, 60));

    // Same user id on purpose: the tier picks the limiter, so these must not collide.
    User freeUser(7, UserTier::FREE);
    User premiumUser(7, UserTier::PREMIUM);

    check("free 1", service.allowRequest(&freeUser), true);
    check("free 2 (limit is 1)", service.allowRequest(&freeUser), false);

    check("premium 1", service.allowRequest(&premiumUser), true);
    check("premium 2", service.allowRequest(&premiumUser), true);
    check("premium 3", service.allowRequest(&premiumUser), true);
}

void testUnregisteredTierIsDenied(){
    std::cout << "\n== Tier with no configured limiter is denied ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(10, 60));

    User premiumUser(8, UserTier::PREMIUM);
    check("premium request with no PREMIUM limiter", service.allowRequest(&premiumUser), false);
}

void testUnknownAlgorithmIsIgnored(){
    std::cout << "\n== Factory returns nullptr for an unknown algorithm ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "leaky_bucket", new RateLimiterConfig(10, 60));

    User alice(9, UserTier::FREE);
    check("request after failed registration", service.allowRequest(&alice), false);
}

void testConcurrency(){
    std::cout << "\n== Concurrency: 8 threads x 50 requests, quota 100 ==\n";

    RateLimiterService service;
    service.addNewRateLimiter(UserTier::FREE, "fixed_window", new RateLimiterConfig(100, 3600));

    const int threadCount = 8;
    const int requestsPerThread = 50;
    std::atomic<int> allowed(0);

    std::vector<std::thread> workers;
    for(int t = 0; t < threadCount; t++){
        workers.emplace_back([&service, requestsPerThread, &allowed](){
            User user(42, UserTier::FREE);
            for(int i = 0; i < requestsPerThread; i++){
                if(service.allowRequest(&user)) allowed++;
            }
        });
    }
    for(auto& w : workers) w.join();

    checkEquals("total allowed across all threads", allowed.load(), 100);
}

int main(){
    testFixedWindow();
    testFixedWindowIsolatesUsers();
    testTokenBucket();
    testTokenBucketDoesNotOverfill();
    testTokenBucketSustainedRate();
    testReRegisteringATierReplacesTheLimiter();
    testTiersAreIndependent();
    testUnregisteredTierIsDenied();
    testUnknownAlgorithmIsIgnored();
    testConcurrency();

    std::cout << "\n---------------------------------------------\n";
    std::cout << (testsRun - testsFailed) << "/" << testsRun << " checks passed\n";
    return testsFailed == 0 ? 0 : 1;
}
