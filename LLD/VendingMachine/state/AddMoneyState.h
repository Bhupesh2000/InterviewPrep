#ifndef ADD_MONEY_STATE_H
#define ADD_MONEY_STATE_H

#include "../VendingMachine.h"
#include "./StateFactory.h"

class AddMoneyState : public State{
public:
    std::string getName() override{
        return "AddMoneyState";
    }

    // Self loop, the customer keeps feeding notes in until they pick something.
    void insertCash(VendingMachine* machine, Currency note, int qty) override{
        if(qty <= 0){
            std::cout << "  quantity must be positive" << std::endl;
            return;
        }
        machine -> getPurchase() -> addMoney(note, qty);
    }

    void selectItem(VendingMachine* machine, int shelfId, int qty) override{
        // A rejected pick leaves the machine here so the customer can try another
        // shelf without losing the money already staged.
        if(!addSelection(machine, shelfId, qty)) return;
        machine -> setState(StateFactory::selectItem());
    }

    void cancel(VendingMachine* machine) override{
        abortTransaction(machine, "cancelled");
    }
};

#endif
