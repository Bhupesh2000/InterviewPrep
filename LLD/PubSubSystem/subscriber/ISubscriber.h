#ifndef I_SUBSCRIBER_H
#define I_SUBSCRIBER_H

#include "../model/Message.h"

class ISubscriber{
public:
    virtual ~ISubscriber() = default;
    virtual void OnMessage(const Message& m) = 0;
    virtual const std::string getName() const = 0;
};

#endif