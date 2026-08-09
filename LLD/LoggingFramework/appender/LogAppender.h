#ifndef LOG_APPENDER_H
#define LOG_APPENDER_H

#include <mutex>

#include "../formatter/Formatter.h"

class LogAppender{
protected:
    Formatter* formatter;

    // Guards this appender's destination only. That is safe exactly as long as
    // two appenders never write to the same destination - see ConsoleAppender
    // (owns std::cout) and FileAppender (owns its own file).
    std::mutex mtx;

public:
    explicit LogAppender(Formatter* formatter) : formatter(formatter){};
    virtual ~LogAppender() = default;

    // const Message& : no copy of the message on the logging path.
    virtual void appendMessage(const Message& m) = 0;
};

#endif
