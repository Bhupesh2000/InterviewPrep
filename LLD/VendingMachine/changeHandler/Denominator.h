#ifndef DENOMINATOR_H
#define DENOMINATOR_H

#include "./ChangeHandler.h"

class Denominator : public ChangeHandler{
    Currency note;

protected:
    Currency getDenomination() override{
        return note;
    }

public:
    Denominator(Currency note) : note(note){};
};

#endif