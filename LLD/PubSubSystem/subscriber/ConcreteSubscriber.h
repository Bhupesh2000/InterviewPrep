#ifndef CONCRETE_SUBSCRIBER_H
#define CONCRETE_SUBSCRIBER_H

#include <string>
#include <iostream>

#include "../model/Message.h"
#include "./ISubscriber.h"

class ConcreteSubscriber : public ISubscriber{
    const std::string name; 
public:
    explicit ConcreteSubscriber(const std::string& name) : name(name){};

    void OnMessage(const Message& m) override{
        const std::string payload = m.getPayload();
        std::cout << "Payload received : " << payload << std::endl;
    }

    const std::string getName() const override{
        return name;
    }
    
};

#endif