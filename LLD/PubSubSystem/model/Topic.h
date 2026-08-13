#ifndef TOPIC_H
#define TOPIC_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <mutex>
#include "./Message.h"
#include "../subscriber/ISubscriber.h"

class Topic{
    const std::string name;
    std::unordered_set<ISubscriber*> subs;
    std::mutex subsMtx;

public:
    Topic(const std::string& name) : name(name){};

    void subscribe(ISubscriber* sub){
        std::lock_guard<std::mutex> lock(subsMtx);
        auto it = subs.find(sub);
        if(it == subs.end()){
            subs.insert(sub);
        }
        else std::cout << "Already subscribed" << std::endl;
    }

    void unsubscribe(ISubscriber* sub){
        std::lock_guard<std::mutex> lock(subsMtx);
        auto it = subs.find(sub);
        if(it != subs.end()){
            subs.erase(sub);
        }
        else std::cout << "Not subscribed" << std::endl;
    }

    void notifySubscribers(const Message& m){
        std::vector<ISubscriber*> subsSnapshot;
        {
            std::lock_guard<std::mutex> lock(subsMtx);
            for(auto it : subs){
                subsSnapshot.push_back(it);
            }
        }

        for(auto it : subsSnapshot){
            it -> OnMessage(m);
        }
    }
};

#endif