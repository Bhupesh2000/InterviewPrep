#ifndef REFILL_INVENTORY_STATE_H
#define REFILL_INVENTORY_STATE_H

#include "../VendingMachine.h"
#include "./StateFactory.h"

class RefillInventoryState : public State{
public:
    std::string getName() override{
        return "RefillInventoryState";
    }

    // Self loop, the operator loads one shelf at a time.
    void addInventory(VendingMachine* machine, int shelfId, int itemId, int qty) override{
        if(!machine -> getInventory() -> refillItem(shelfId, itemId, qty)){
            std::cout << "  cannot put item " << itemId << " on shelf " << shelfId << std::endl;
        }
    }

    // Confirm ends the maintenance session, there is no transaction to settle.
    void confirm(VendingMachine* machine) override{
        machine -> setState(StateFactory::idle());
    }
};

#endif
