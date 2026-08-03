#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "./model/Purchase.h"
#include "./model/Inventory.h"
#include "./model/CashHolder.h"
#include "./state/State.h"

class VendingMachine{
    Inventory* inventory;
    CashHolder* cashHolder;
    State* currState;
    Purchase* purchase;

public:
    VendingMachine(State* initialState){
        inventory = new Inventory();
        cashHolder = new CashHolder();
        // One Purchase for the machine's lifetime, reset between customers
        // rather than reallocated, so getPurchase() is never null.
        purchase = new Purchase();
        currState = initialState;
    }

    ~VendingMachine(){
        delete inventory;
        delete cashHolder;
        delete purchase;
    }

    Inventory* getInventory(){
        return inventory;
    }

    CashHolder* getCashHolder(){
        return cashHolder;
    }

    Purchase* getPurchase(){
        return purchase;
    }

    State* getState(){
        return currState;
    }

    void setState(State* state){
        currState = state;
        std::cout << "  -> machine is now in " << state -> getName() << std::endl;
    }

    void insertCash(Currency note, int qty){
        currState -> insertCash(this, note, qty);
    }

    void selectItem(int shelfId, int qty){
        currState -> selectItem(this, shelfId, qty);
    }

    void confirm(){
        currState -> confirm(this);
    }

    void cancel(){
        currState -> cancel(this);
    }

    // Operator facing operations, delegated the same way.
    void addInventory(int shelfId, int itemId, int qty){
        currState -> addInventory(this, shelfId, itemId, qty);
    }

    void refillCash(Currency note, int qty){
        currState -> refillCash(this, note, qty);
    }

    // Hands the customer their money back untouched. Used on cancel and whenever
    // a sale cannot be completed. The cash never entered the CashHolder, so this
    // is only a report plus a reset.
    void refund(){
        std::unordered_map<Currency, int> cash = purchase -> getStagedMoney();
        int amount = cashHolder -> totalOf(cash);
        if(amount > 0) std::cout << "  refunding " << amount << " to the customer" << std::endl;
        purchase -> reset();
    }
    
};

#endif