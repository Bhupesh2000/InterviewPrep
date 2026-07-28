#ifndef I_PAYMENT_STRATEGY_H
#define I_PAYMENT_STRATEGY_H

class IPaymentStrategy{
public:
    IPaymentStrategy() = default;
    virtual ~IPaymentStrategy() = default;
    virtual void pay(int amount) = 0; 
};

#endif