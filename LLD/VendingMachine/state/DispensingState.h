#ifndef DISPENSING_STATE_H
#define DISPENSING_STATE_H

#include <optional>
#include <unordered_map>
#include "../VendingMachine.h"
#include "./StateFactory.h"

class DispensingState : public State{
public:
    std::string getName() override{
        return "DispensingState";
    }

    // Reached only from SelectItemState, which has already vetted stock, payment
    // and change. This is where the transaction is actually committed, so the
    // order of the two commits matters: stock is probed with hasStock, the cash
    // is settled, and only then is the stock pulled, which by that point cannot
    // fail. Doing it the other way round could take the items off the shelf and
    // then discover the cash cannot be settled.
    void confirm(VendingMachine* machine) override{
        Purchase* purchase = machine -> getPurchase();
        Inventory* inventory = machine -> getInventory();
        CashHolder* cashHolder = machine -> getCashHolder();

        std::unordered_map<int, int> selected = purchase -> getSelectedItems();
        std::unordered_map<Currency, int> staged = purchase -> getStagedMoney();
        int changeDue = cashHolder -> totalOf(staged) - purchase -> getTotalPrice(inventory);

        if(!inventory -> hasStock(selected)){
            abortTransaction(machine,"item unavailable");
            return;
        }

        std::optional<std::unordered_map<Currency, int>> change = cashHolder -> completeSale(staged, changeDue);
        if(!change.has_value()){
            abortTransaction(machine,"change unavailable");
            return;
        }

        std::unordered_map<Item*, int> order = inventory -> getItems(selected).value();
        for(auto it : order){
            std::cout << "  dispensing item " << it.first -> getId() << " x" << it.second << std::endl;
        }

        int changeAmount = cashHolder -> totalOf(change.value());
        if(changeAmount > 0) std::cout << "  returning change of " << changeAmount << std::endl;

        // The sale is settled, so the same Purchase can serve the next customer.
        purchase -> reset();
        machine -> setState(StateFactory::idle());
    }
};

#endif
