#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "../VendingMachine.h"
#include "./StateFactory.h"

class IdleState : public State{
public:
    std::string getName() override{
        return "IdleState";
    }

    void insertCash(VendingMachine* machine, Currency note, int qty) override{
        machine -> getPurchase() -> addMoney(note, qty);
        machine -> setState(StateFactory::addMoney());
    }

    void refillCash(VendingMachine* machine, Currency note, int qty) override{
        machine -> getCashHolder() -> add(note, qty);
        machine -> setState(StateFactory::refillCash());
    }

    void addInventory(VendingMachine* machine, int shelfId, int itemId, int qty) override{
        machine -> getInventory() -> refillItem(shelfId, itemId, qty);
        machine -> setState(StateFactory::refillInventory());
    }
};

#endif