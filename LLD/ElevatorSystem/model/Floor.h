#ifndef FLOOR_H
#define FLOOR_H

#include "./ExternalButton.h"

class Floor{
    int id;
    ExternalButton* upButton;
    ExternalButton* downButton;

public:
    Floor(int id) : id(id){};

    void pressUpButton(){
        upButton -> pressButton();
    }

    void pressDownButton(){
        downButton -> pressButton();
    }

    void addExternalButton(ExternalButton* upButton){
        this -> upButton = upButton;
    }

    void addInternalButton(ExternalButton* downButton){
        this -> downButton = downButton;
    }

    int getId(){
        return id;
    }
};

#endif