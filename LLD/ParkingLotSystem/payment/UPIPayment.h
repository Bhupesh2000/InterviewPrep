#ifndef UPI_PAYMENT_H
#define UPI_PAYMENT_H

#include <iostream>
#include "./IPaymentStrategy.h"

class UPIPayment : public IPaymentStrategy{
public:
    void pay(int amount) override{
        std::cout << "Payment of  "<< amount <<" made through UPI" << std::endl;
    };
};

#endif