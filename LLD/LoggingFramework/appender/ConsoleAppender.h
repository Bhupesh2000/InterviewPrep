#ifndef CONSOLE_APPENDER_H
#define CONSOLE_APPENDER_H

#include <iostream>
#include <string>

#include "./LogAppender.h"

class ConsoleAppender : public LogAppender{
public:
    explicit ConsoleAppender(Formatter* formatter) : LogAppender(formatter){};

    void appendMessage(const Message& m) override{
        // Formatting no longer touches shared state, so it can happen outside
        // the lock; the mutex only has to cover the write to std::cout.
        std::string record = formatter->format(m);

        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Writing to console : " << record;
    }
};

#endif
