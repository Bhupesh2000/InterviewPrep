#ifndef ITEM_H
#define ITEM_H

class Item{
    int id;
    int price;

public:
    Item(int id, int price) : id(id), price(price){};
    
    const int getId(){
        return id;
    }

    const int getPrice(){
        return price;
    }
};

#endif