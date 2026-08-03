#ifndef CURRENCY_H
#define CURRENCY_H

enum class Currency{
    ONE = 1,
    TWO = 2,
    FIVE = 5,
    TEN = 10,
    TWENTY = 20,
    FIFTY = 50,
    HUNDRED = 100
};

inline int getValue(Currency c){
    return static_cast<int>(c);
}

#endif