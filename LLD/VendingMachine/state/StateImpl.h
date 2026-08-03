#ifndef STATE_IMPL_H
#define STATE_IMPL_H

// Assembly point for the state machine. State.h only forward declares
// VendingMachine and StateFactory.h only declares its lookups, which is what
// keeps those headers free of cycles. Everything is complete by the time this
// header is done, so the bodies that need both sides live here.

#include "../VendingMachine.h"
#include "./StateFactory.h"
#include "./AddMoneyState.h"
#include "./DispensingState.h"
#include "./IdleState.h"
#include "./RefillCashState.h"
#include "./RefillInventoryState.h"
#include "./SelectItemState.h"

inline bool State::addSelection(VendingMachine* machine, int shelfId, int qty){
    if(qty <= 0){
        std::cout << "  quantity must be positive" << std::endl;
        return false;
    }

    Purchase* purchase = machine -> getPurchase();

    // Checked against the running selection rather than this request alone, so
    // two picks from the same shelf cannot together overdraw it.
    std::unordered_map<int, int> wanted = purchase -> getSelectedItems();
    wanted[shelfId] += qty;

    if(!machine -> getInventory() -> hasStock(wanted)){
        std::cout << "  shelf " << shelfId << " cannot supply "
                  << wanted[shelfId] << " item(s)" << std::endl;
        return false;
    }

    purchase -> addItem(shelfId, qty);
    return true;
}

inline void State::abortTransaction(VendingMachine* machine, const std::string& reason){
    std::cout << "  " << reason << std::endl;
    machine -> refund();
    machine -> setState(StateFactory::idle());
}

// One instance per state, shared by every machine. The states hold no data of
// their own, everything they touch arrives through the VendingMachine argument.
inline State* StateFactory::idle(){
    static IdleState instance;
    return &instance;
}

inline State* StateFactory::addMoney(){
    static AddMoneyState instance;
    return &instance;
}

inline State* StateFactory::selectItem(){
    static SelectItemState instance;
    return &instance;
}

inline State* StateFactory::dispense(){
    static DispensingState instance;
    return &instance;
}

inline State* StateFactory::refillCash(){
    static RefillCashState instance;
    return &instance;
}

inline State* StateFactory::refillInventory(){
    static RefillInventoryState instance;
    return &instance;
}

#endif
