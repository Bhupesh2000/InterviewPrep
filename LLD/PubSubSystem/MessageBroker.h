#ifndef MESSAGE_BROKER_H
#define MESSAGE_BROKER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <shared_mutex>
#include "./model/Topic.h"
#include "./subscriber/ISubscriber.h"

class MessageBroker{
    std::unordered_map<std::string, Topic*> topics;
    std::shared_mutex topicsMtx;

    MessageBroker(){};

    ~MessageBroker(){
        for(auto it : topics){
            delete it.second;
        }
    }

    Topic* getTopic(const std::string& topicName){
        std::shared_lock<std::shared_mutex> lock_guard(topicsMtx);
        auto it = topics.find(topicName);
        if(it == topics.end()){
            return nullptr;
        }
        else return it -> second;
    }

public:
    static MessageBroker* getInstance(){
        static MessageBroker instance;
        return &instance;
    }

    MessageBroker(const MessageBroker&) = delete;
    MessageBroker& operator=(const MessageBroker&) = delete;

    Topic* createTopic(const std::string& topicName){
       Topic* topic = nullptr;
       {
            std::unique_lock<std::shared_mutex> lock(topicsMtx);
            auto it = topics.find(topicName);
            if(it == topics.end()){
                topic = new Topic(topicName);
                topics[topicName] = topic;
            }
            else topic = it -> second;
       }
       return topic;
    }

    void subscribe(const std::string& topicName, ISubscriber* sub){
        Topic* topic = getTopic(topicName);
        if(topic != nullptr) topic -> subscribe(sub);
        else std::cout << "Unregistered topic" << std::endl;
    }

    void unsubscribe(const std::string& topicName, ISubscriber* sub){
        Topic* topic = getTopic(topicName);
        if(topic != nullptr) topic -> unsubscribe(sub);
        else std::cout << "Unregistered topic" << std::endl;
    }

    void publish(const std::string& payload, const std::string& topicName){
        Topic* topic = getTopic(topicName);
        if(topic != nullptr){
            topic -> notifySubscribers(Message(payload, topicName));
        }
        else std::cout << "Unregistered topic" << std::endl;
    }
};

#endif