#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>

class Message{
    const std::string payload;
    const std::string topicName;
    const std::chrono::system_clock::time_point timestamp;

public:
    Message(const std::string& payload, const std::string& topicName) : 
        payload(payload), topicName(topicName), timestamp(std::chrono::system_clock::now()){};

    const std::string getPayload() const{
        return payload;
    }

    const std::string getTopicName() const{
        return topicName;
    }

    const std::chrono::system_clock::time_point getTimeStamp() const{
        return timestamp;
    }
};

#endif