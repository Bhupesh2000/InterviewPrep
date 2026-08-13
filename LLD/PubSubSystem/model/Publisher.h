#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include "../MessageBroker.h"

class Publisher{
    MessageBroker* broker;

public:
    explicit Publisher(MessageBroker* broker) : broker(broker){};

    void publish(const std::string& payload, const std::string& topicName){
        broker -> publish(payload, topicName);
    }
};

#endif