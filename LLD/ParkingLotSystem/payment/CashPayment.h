#ifndef CASH_PAYMENT_H
#define CASH_PAYMENT_H

#include <iostream>
#include "./IPaymentStrategy.h"

class CashPayment : public IPaymentStrategy{
public:
    void pay(int amount) override{
        std::cout << "Payment of  "<< amount <<" made through Cash" << std::endl;
    };
};

#endif