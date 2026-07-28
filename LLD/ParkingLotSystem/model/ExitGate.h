#ifndef EXIT_GATE_H
#define EXIT_GATE_H

#include <string>
#include "./ParkingBuilding.h"
#include "../pricing/CostComputation.h"
#include "../payment/IPaymentStrategy.h"
#include "../payment/UPIPayment.h"
#include "../payment/CashPayment.h"
#include "./Ticket.h"

class ExitGate{
    ParkingBuilding* building;
    CostComputation* costComputation;

public:
    ExitGate(ParkingBuilding* building, CostComputation* costComputation) :
        building(building), costComputation(costComputation){};

    ~ExitGate(){
        delete costComputation;
    }

    void exit(Ticket* ticket, IPaymentStrategy* paymentStrategy){
        if(ticket == nullptr || paymentStrategy == nullptr) return;
        // Claiming the ticket first means a second exit for the same vehicle
        // returns here, so the spot is freed and charged exactly once. No gate
        // wide lock is needed, the spot is guarded by the manager that owns it.
        if(!ticket -> tryDeactivate()) return;

        std::string timeOfExit = "01:01:2026 11:01:01";
        ticket -> setTimeOfExit(timeOfExit);
        building -> unpark(ticket -> getFloorId(), ticket -> getVehicleType(), ticket -> getParkingSpot());
        int amountToPay = costComputation -> calculateParkingFair(ticket);
        paymentStrategy -> pay(amountToPay);
    }
};

#endif