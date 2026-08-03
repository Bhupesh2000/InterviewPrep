#include <iostream>
#include "./VendingMachine.h"
#include "./state/StateImpl.h"

void scenario(const std::string& title){
    std::cout << std::endl << "=== " << title << " ===" << std::endl;
}

int main(){
    VendingMachine machine(StateFactory::idle());

    // Catalogue of what this machine is able to sell. Registering is a setup
    // step rather than a state transition, so it goes straight to the inventory.
    Item* chips = new Item(101, 20);
    Item* soda = new Item(102, 15);
    machine.getInventory() -> regsiterItem(101, chips);
    machine.getInventory() -> regsiterItem(102, soda);

    scenario("operator stocks the shelves");
    machine.addInventory(1, 101, 5);        // Idle -> RefillInventory
    machine.addInventory(2, 102, 3);        // self loop
    machine.confirm();                      // -> Idle

    scenario("operator loads the float");
    machine.refillCash(Currency::TEN, 10);  // Idle -> RefillCash
    machine.refillCash(Currency::FIVE, 10); // self loop
    machine.refillCash(Currency::ONE, 20);
    machine.confirm();                      // -> Idle

    scenario("happy path");
    machine.insertCash(Currency::FIFTY, 1); // Idle -> AddMoney
    machine.insertCash(Currency::TEN, 1);   // self loop
    machine.selectItem(1, 2);               // -> ItemSelection
    machine.selectItem(2, 1);               // self loop
    machine.confirm();                      // -> Dispensing -> Idle

    scenario("customer changes their mind");
    machine.insertCash(Currency::TWENTY, 1);
    machine.cancel();                       // refund -> Idle

    scenario("not enough money");
    machine.insertCash(Currency::ONE, 1);
    machine.selectItem(1, 1);
    machine.confirm();                      // refund -> Idle

    scenario("shelf cannot cover the request");
    machine.insertCash(Currency::HUNDRED, 1);
    machine.selectItem(1, 99);              // refused, machine stays in AddMoney
    machine.cancel();                       // refund -> Idle

    scenario("actions the current state does not accept");
    machine.confirm();                      // Idle cannot confirm
    machine.selectItem(1, 1);               // Idle cannot select

    // Inventory only keeps borrowed pointers to the catalogue, so the items are
    // owned here.
    delete chips;
    delete soda;

    return 0;
}
