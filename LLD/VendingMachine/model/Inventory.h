#ifndef INVENTORY_H
#define INVENTORY_H

#include <optional>
#include <unordered_map>
#include "./Shelf.h"

class Inventory{
    std::unordered_map<int, Shelf*> shelves;
    std::unordered_map<int, Item*> items;

public:
    Inventory(){
        for(int i = 1; i < 9; i++){
            shelves[i] = new Shelf(i);
        }
    }

    ~Inventory(){
        for(auto it : shelves) delete it.second;
        items.clear();
    }

    void regsiterItem(int itemId, Item* item){
        items[itemId] = item;
    }

    bool removeItem(int shelfId, int qty){
        if(qty < 0) return false;
        if(shelves.count(shelfId) != 0) return shelves[shelfId] -> removeItem(qty);
        return false;
    }

    bool refillItem(int shelfId, int itemId, int qty){
        if(qty < 0) return false;
        if(items.count(itemId) == 0 || shelves.count(shelfId) == 0) return false;
        return shelves[shelfId] -> addItem(items[itemId], qty);
    }

    int getPrice(int shelfId){
        if(shelves.count(shelfId) != 0) return shelves[shelfId] -> getPrice();
        return -1;
    }

    // all or nothing
    // itemList is map of type shelfId => qty
    bool hasStock(std::unordered_map<int, int> itemsList){
        for(auto it : itemsList){
            if(shelves.count(it.first) == 0 || !shelves[it.first] -> hasStock(it.second)) return false; 
        }
        return true;
    }

    // all or nothing
    std::optional<std::unordered_map<Item*, int>> getItems(std::unordered_map<int, int> itemsList){
        if(!hasStock(itemsList)) return {};
        std::unordered_map<Item*, int> order;
        for(auto it : itemsList){
            Item* item = shelves[it.first] -> getItem();
            order[item] += it.second;
            shelves[it.first] -> removeItem(it.second);
        }

        return order;
    }
};

#endif