#ifndef CASH_HOLDER_H
#define CASH_HOLDER_H

#include <optional>
#include <unordered_map>
#include "../enum/Currency.h"
#include "../changeHandler/Denominator.h"

class CashHolder{
    std::unordered_map<Currency, int> machineCash;
    ChangeHandler* changeHandler;

public:
    CashHolder(){
        changeHandler = new Denominator(Currency :: HUNDRED);
        changeHandler -> setNext(new Denominator(Currency :: FIFTY))
                    -> setNext(new Denominator(Currency :: TWENTY))
                    -> setNext(new Denominator(Currency :: TEN))
                    -> setNext(new Denominator(Currency :: FIVE))
                    -> setNext(new Denominator(Currency :: TWO))
                    -> setNext(new Denominator(Currency :: ONE));
    }

    ~CashHolder(){
        delete changeHandler;
    }

    bool add(Currency note, int qty){
        if(qty < 0) return false;
        machineCash[note] += qty;
        return true;
    }

    // remove only those possible
    bool remove(Currency note, int qty){
        if(qty < 0) return false;
        machineCash[note] -= qty;
        return true;
    }

    std::optional<std::unordered_map<Currency, int>> returnChange(int amount, std::unordered_map<Currency, int>& stagedCash){
        if(amount < 0) return {};
        std::unordered_map<Currency, int> change;
        if(changeHandler -> handle(amount, machineCash, stagedCash, change)) return change;
        else return {};
    }

    std::optional<std::unordered_map<Currency, int>> completeSale(std::unordered_map<Currency, int>& stagedCash, int changeAmount){
        std::unordered_map<Currency, int> change;
        
        if(changeAmount < 0 || !changeHandler -> handle(changeAmount, machineCash, stagedCash, change)) return {};

        // Commit staged
        for(auto it : stagedCash){
            add(it.first, it.second);
        }
        
        // remove change amount
        for(auto it : change){
            remove(it.first, it.second);
        }

        return change;
    }

    int totalOf(const std::unordered_map<Currency, int>& cash){
        int total = 0;
        for(auto it : cash){
            total += getValue(it.first) * it.second;
        }
        return total;
    }
};

#endif