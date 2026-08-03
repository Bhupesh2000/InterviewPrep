#ifndef REFILL_CASH_STATE_H
#define REFILL_CASH_STATE_H

#include "../VendingMachine.h"
#include "./StateFactory.h"

class RefillCashState : public State{
public:
    std::string getName() override{
        return "RefillCashState";
    }

    // Self loop, the operator tops up one denomination at a time.
    void refillCash(VendingMachine* machine, Currency note, int qty) override{
        if(!machine -> getCashHolder() -> add(note, qty)){
            std::cout << "  quantity must be positive" << std::endl;
        }
    }

    // Confirm ends the maintenance session, there is no transaction to settle.
    void confirm(VendingMachine* machine) override{
        machine -> setState(StateFactory::idle());
    }
};

#endif
