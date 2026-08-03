#ifndef CHANGE_HANDLER_H
#define CHANGE_HANDLER_H

#include <algorithm>
#include <unordered_map>
#include "../enum/Currency.h"

class ChangeHandler{
    ChangeHandler* next;

    // find() on an absent denomination returns end(), so counts are read through
    // here rather than dereferencing the iterator straight away.
    static int countOf(std::unordered_map<Currency, int>& cash, Currency note){
        auto it = cash.find(note);
        return it == cash.end() ? 0 : it -> second;
    }

protected:
    virtual Currency getDenomination() = 0;

public:
    ChangeHandler() : next(nullptr){};
    virtual ~ChangeHandler(){ delete next;}

    ChangeHandler* setNext(ChangeHandler* nextHandler){
        next = nextHandler;
        return next;
    }

    bool handle(int amount, std::unordered_map<Currency, int>& availableInMachine, std::unordered_map<Currency, int>& staged, std::unordered_map<Currency, int>& change){
        if(amount == 0) return true;
        if(amount < 0) return false;

        Currency note = getDenomination();
        int value = getValue(note);
        int available = countOf(availableInMachine, note) + countOf(staged, note);

        int maxToBeUsed = std::min(amount / value, available);

        // Can't directly apply greedy here
        // Eg. amount = 600, (500 => 1, 200 => 3)
        // Greedy will first choose 500 and remaining 100 won't be fulfilled
        // Else choose 200 * 3 notes, hence every count needs to be checked
        for(int count = maxToBeUsed; count >= 0; count--){
            int remaining = amount - value * count;

            if(remaining == 0){
                if(count > 0) change[note] = count;
                return true;
            }

            if(next == nullptr) continue;

            // Tentatively commit this link's notes and let the rest of the chain try.
            if(count > 0) change[note] = count;
            if(next -> handle(remaining, availableInMachine, staged, change)) return true;
            change.erase(note);
        }

        // No combination from this link down adds up to the amount.
        return false;
    }
};

#endif
