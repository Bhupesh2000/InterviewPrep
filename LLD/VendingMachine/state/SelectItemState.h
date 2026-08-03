#ifndef SELECT_ITEM_STATE_H
#define SELECT_ITEM_STATE_H

#include <unordered_map>
#include "../VendingMachine.h"
#include "./StateFactory.h"

class SelectItemState : public State{
public:
    std::string getName() override{
        return "SelectItemState";
    }

    // Self loop, the customer can keep adding to the basket.
    void selectItem(VendingMachine* machine, int shelfId, int qty) override{
        addSelection(machine, shelfId, qty);
    }

    // Gate in front of Dispensing. Nothing is committed here, these checks only
    // decide whether the sale is allowed to go through at all, and every failure
    // hands the money back and returns the machine to Idle.
    void confirm(VendingMachine* machine) override{
        Purchase* purchase = machine -> getPurchase();
        Inventory* inventory = machine -> getInventory();
        CashHolder* cashHolder = machine -> getCashHolder();

        std::unordered_map<int, int> selected = purchase -> getSelectedItems();
        if(selected.empty()){
            std::cout << "  nothing selected yet" << std::endl;
            return;
        }

        // Re-checked because a refill or another sale may have moved the shelf
        // since the item was picked.
        if(!inventory -> hasStock(selected)){
            abortTransaction(machine,"item unavailable");
            return;
        }

        std::unordered_map<Currency, int> staged = purchase -> getStagedMoney();
        int paid = purchase -> totalAmountPaid();
        int price = purchase -> getTotalPrice(inventory);

        if(paid < price){
            abortTransaction(machine,"insufficient money");
            return;
        }

        // Probe only. returnChange works out a breakdown without touching the
        // float, so the sale is refused up front if the machine cannot pay the
        // difference back.
        if(!cashHolder -> returnChange(paid - price, staged).has_value()){
            abortTransaction(machine,"change unavailable");
            return;
        }

        // One confirm() from the customer, so dispensing is driven from here
        // rather than waiting on a second press.
        machine -> setState(StateFactory::dispense());
        machine -> confirm();
    }

    void cancel(VendingMachine* machine) override{
        abortTransaction(machine, "cancelled");
    }
};

#endif
