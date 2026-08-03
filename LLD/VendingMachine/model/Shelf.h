#ifndef SHELF_H
#define SHELF_H

#include "./Item.h"

class Shelf{
    int id;
    Item* item;
    int qty;

public:
    Shelf(int id) : id(id), item(nullptr), qty(0){};

    Item* getItem(){
        return item;
    }

    int getQty(){
        return qty;
    }

    // -1 on an empty shelf, matching what Inventory reports for a shelf that
    // does not exist, so callers have a single "no price" answer to test for.
    int getPrice(){
        if(item == nullptr) return -1;
        return item -> getPrice();
    }

    bool addItem(Item* itemToBeAdded, int qtyToBeAdded){
        if(qtyToBeAdded < 0) return false;
        if(item != nullptr && item != itemToBeAdded) return false;
        item = itemToBeAdded;
        qty += qtyToBeAdded;
        return true;
    }

    bool removeItem(int qtyToBeRemoved){
        if(qty < qtyToBeRemoved || qtyToBeRemoved < 0) return false;
        qty -= qtyToBeRemoved;
        return true;
    }

    bool hasStock(int qty){
        return this -> qty >= qty;
    }
};

#endif
