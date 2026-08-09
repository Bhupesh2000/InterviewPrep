#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

// std::ctime / std::localtime return a pointer into a single static buffer that
// is shared by every thread in the process, so two threads formatting a message
// at the same time corrupt each other's result. localtime_r fills a caller-owned
// std::tm instead, which keeps formatting free of shared state.
inline std::string formatTimestamp(std::chrono::system_clock::time_point tp){
    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    std::tm tmBuf{};
    localtime_r(&t, &tmBuf);   // POSIX; the Windows equivalent is localtime_s

    std::ostringstream out;
    out << std::put_time(&tmBuf, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

#endif
