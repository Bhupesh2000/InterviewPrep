#include <iostream>
#include <thread>
#include <vector>

#include "ElevatorApp.h"
#include "./enum/Direction.h"

void externalRequests(ElevatorApp& app){
    app.pressExternalButton(5, Direction::UP);
    app.pressExternalButton(10, Direction::DOWN);
    app.pressExternalButton(15, Direction::UP);
    app.pressExternalButton(7, Direction::DOWN);
}

void internalRequests(ElevatorApp& app){
    app.pressInternalButton(0, 12);
    app.pressInternalButton(1, 7);
    app.pressInternalButton(2, 18);
    app.pressInternalButton(0, 3);
}

int main(){

    ElevatorApp app(20, 3);

    std::vector<std::thread> threads;

    threads.emplace_back(externalRequests, std::ref(app));
    threads.emplace_back(internalRequests, std::ref(app));

    for(std::thread& t : threads){
        t.join();
    }

    std::cout << "Elevator system test completed." << std::endl;

    return 0;
}