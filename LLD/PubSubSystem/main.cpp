#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "MessageBroker.h"
#include "model/Publisher.h"
#include "subscriber/ConcreteSubscriber.h"

int main(){
    MessageBroker* broker = MessageBroker::getInstance();

    broker -> createTopic("sports");
    broker -> createTopic("weather");

    ConcreteSubscriber alice("Alice");
    ConcreteSubscriber bob("Bob");
    ConcreteSubscriber carol("Carol");

    std::cout << "--- subscribe ---" << std::endl;
    broker -> subscribe("sports", &alice);
    broker -> subscribe("sports", &bob);
    broker -> subscribe("weather", &carol);
    broker -> subscribe("sports", &alice);      // duplicate -> "Already subscribed"
    broker -> subscribe("politics", &alice);    // unknown  -> "Unregistered topic"

    std::cout << "--- publish ---" << std::endl;
    Publisher publisher(broker);
    publisher.publish("India won the match", "sports");     // Alice + Bob
    publisher.publish("Rain expected today", "weather");    // Carol
    publisher.publish("Election results", "politics");      // Unregistered topic

    std::cout << "--- unsubscribe ---" << std::endl;
    broker -> unsubscribe("sports", &bob);
    broker -> unsubscribe("sports", &bob);                  // again -> "Not subscribed"
    publisher.publish("Second innings started", "sports");  // Alice only

    std::cout << "--- concurrent publishers ---" << std::endl;
    std::vector<std::thread> threads;
    for(int i = 0; i < 4; i++){
        threads.emplace_back([broker, i]{
            Publisher p(broker);
            for(int j = 0; j < 3; j++){
                p.publish("update " + std::to_string(i) + "." + std::to_string(j), "weather");
            }
        });
    }
    for(auto& t : threads) t.join();

    return 0;
}
