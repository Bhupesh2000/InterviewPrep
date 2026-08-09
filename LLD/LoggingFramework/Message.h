#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>

#include "./MessageLevel.h"

class Message{
    const std::string messageString;
    const MessageLevel level;
    const std::chrono::system_clock::time_point timestamp;

public:
    Message(const std::string& messageString, const MessageLevel level) :
        messageString(messageString), level(level), timestamp(std::chrono::system_clock::now()){}

    // Returned by reference: a Message outlives every read of it on the logging
    // path, and returning by value copied the string once per formatter call.
    const std::string& getMessageString() const{
        return messageString;
    }

    MessageLevel getLevel() const{
        return level;
    }

    std::chrono::system_clock::time_point getTimeStamp() const{
        return timestamp;
    }
};

#endif
