#ifndef STATE_FACTORY_H
#define STATE_FACTORY_H

// Declarations only. The concrete state headers call these to move the machine
// along, and a declaration is all a call site needs, so the factory can be named
// here without dragging in the states themselves. The bodies are in StateImpl.h.
class State;

class StateFactory{
public:
    static State* idle();
    static State* addMoney();
    static State* selectItem();
    static State* dispense();
    static State* refillCash();
    static State* refillInventory();
};

#endif
