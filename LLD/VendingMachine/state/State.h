#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../enum/Currency.h"

// Forward declared rather than included: VendingMachine.h needs State to be a
// complete type for its inline delegations, so including it back here would make
// the two headers mutually dependent. The bodies that actually reach through the
// machine live in StateImpl.h, where both types are known.
class VendingMachine;

class State{
protected:
    void reject(const std::string& action){
        std::cout << "[" << getName() << "] cannot " << action << " right now" << std::endl;
    }

    // Shared by AddMoneyState and SelectItemState, the two states the diagram
    // lets a customer pick from. Returns false when the pick was not accepted,
    // which is the caller's cue not to move the machine anywhere.
    bool addSelection(VendingMachine* machine, int shelfId, int qty);

    // Every abandoned transaction ends the same way, whether the customer walked
    // away or the machine could not complete the sale.
    void abortTransaction(VendingMachine* machine, const std::string& reason);

public:
    virtual ~State(){};

    virtual std::string getName() = 0;

    virtual void insertCash(VendingMachine* machine, Currency note, int qty){
        reject("insert cash");
    }

    virtual void selectItem(VendingMachine* machine, int shelfId, int qty){
        reject("select an item");
    }

    virtual void confirm(VendingMachine* machine){
        reject("confirm");
    }

    virtual void cancel(VendingMachine* machine){
        reject("cancel");
    }

    // Maintenance operations. The UML lists AddInventoryState and RefillCashState
    // but leaves them off the State interface, which makes them unreachable, so
    // both entry points are declared here.
    virtual void addInventory(VendingMachine* machine, int shelfId, int itemId, int qty){
        reject("add inventory");
    }

    virtual void refillCash(VendingMachine* machine, Currency note, int qty){
        reject("refill cash");
    }
};

#endif
