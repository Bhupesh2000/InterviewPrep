#ifndef PURCHASE_H
#define PURCHASE_H

#include <unordered_map>
#include "../enum/Currency.h"
#include "./Inventory.h"

class Purchase{
    std::unordered_map<int, int> selectedItems;
    std::unordered_map<Currency, int> stagedMoney;

public:
    bool addItem(int shelfId, int qty){
        if(qty <= 0) return false;
        selectedItems[shelfId] += qty;
        return true;
    }

    bool addMoney(Currency c, int qty){
        if(qty <= 0) return false;
        stagedMoney[c] += qty;
        return true;
    }

    int getTotalPrice(Inventory* inv){
        int total = 0;
        for(auto it : selectedItems){
            int price = inv -> getPrice(it.first);
            if(price != -1) total += price * it.second;
        }
        return total;
    }

    int totalAmountPaid(){
        int total = 0;
        for(auto it : stagedMoney){
            total += getValue(it.first) * it.second;
        }
        return total;
    }

    std::unordered_map<int, int> getSelectedItems(){
        return selectedItems;
    }

    std::unordered_map<Currency, int> getStagedMoney(){
        return stagedMoney;
    }

    // Called once the transaction is settled or cancelled, so the same Purchase
    // object can serve the next customer.
    void reset(){
        selectedItems.clear();
        stagedMoney.clear();
    }

};

#endif
