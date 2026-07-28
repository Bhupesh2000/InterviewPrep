#include <iostream>
#include <string>
#include <vector>
#include "./enum/VehicleType.h"
#include "./manager/ParkingSpotManager.h"
#include "./model/ParkingLot.h"
#include "./model/ParkingLevel.h"
#include "./model/ParkingBuilding.h"
#include "./model/Vehicle.h"
#include "./model/Ticket.h"
#include "./parkingLookupStrategy/RandomLookupStrategy.h"
#include "./payment/CashPayment.h"
#include "./payment/UPIPayment.h"
#include "./pricing/CostComputation.h"
#include "./pricing/FixedPricingStrategy.h"

namespace{

std::string typeName(VehicleType type){
    return type == VehicleType::TWO_WHEELER ? "TWO_WHEELER" : "FOUR_WHEELER";
}

// Builds one level holding the requested number of spots per vehicle type.
ParkingLevel* buildLevel(int levelId, int twoWheelerSpots, int fourWheelerSpots){
    ParkingLevel* level = new ParkingLevel(levelId);

    ParkingSpotManager* twoWheelerManager = new ParkingSpotManager(new RandomLookupStrategy());
    for(int i = 0; i < twoWheelerSpots; i ++){
        twoWheelerManager -> addParkingSpot(new ParkingSpot(levelId * 100 + i, VehicleType::TWO_WHEELER));
    }
    level -> addParkingSpotManager(VehicleType::TWO_WHEELER, twoWheelerManager);

    ParkingSpotManager* fourWheelerManager = new ParkingSpotManager(new RandomLookupStrategy());
    for(int i = 0; i < fourWheelerSpots; i ++){
        fourWheelerManager -> addParkingSpot(new ParkingSpot(levelId * 100 + 50 + i, VehicleType::FOUR_WHEELER));
    }
    level -> addParkingSpotManager(VehicleType::FOUR_WHEELER, fourWheelerManager);

    return level;
}

Ticket* parkVehicle(ParkingLot& parkingLot, Vehicle* vehicle){
    Ticket* ticket = parkingLot.allocateSlot(vehicle);
    if(ticket == nullptr){
        std::cout << "[ENTRY] " << vehicle -> getPlateNo() << " (" << typeName(vehicle -> getVehicleType())
                  << ") turned away, no free spot" << std::endl;
        return nullptr;
    }
    std::cout << "[ENTRY] " << vehicle -> getPlateNo() << " (" << typeName(vehicle -> getVehicleType())
              << ") -> ticket #" << ticket -> getId()
              << ", level " << ticket -> getFloorId()
              << ", spot " << ticket -> getParkingSpot() -> getId()
              << ", at " << ticket -> getTimeOfEntry() << std::endl;
    return ticket;
}

void exitVehicle(ParkingLot& parkingLot, Ticket* ticket, IPaymentStrategy* paymentStrategy){
    if(ticket == nullptr) return;
    std::cout << "[EXIT ] ticket #" << ticket -> getId() << " for " << ticket -> getVehiclePlateNo() << " -> ";
    parkingLot.exit(ticket, paymentStrategy);
    std::cout << "        spot " << ticket -> getParkingSpot() -> getId()
              << " is now " << (ticket -> getParkingSpot() -> isSpotFree() ? "free" : "occupied")
              << ", ticket active: " << (ticket -> isActive() ? "yes" : "no") << std::endl;
}

}

int main(){
    // Building: level 1 has 2 two-wheeler + 1 four-wheeler spots, level 2 has 1 + 1.
    ParkingBuilding* building = new ParkingBuilding();
    building -> addLevel(1, buildLevel(1, 2, 1));
    building -> addLevel(2, buildLevel(2, 1, 1));

    CostComputation* costComputation = new CostComputation(new FixedPricingStrategy());
    ParkingLot parkingLot(building, costComputation);

    CashPayment cashPayment;
    UPIPayment upiPayment;

    std::vector<Vehicle*> vehicles = {
        new Vehicle("HR26-1111", VehicleType::TWO_WHEELER),
        new Vehicle("HR26-2222", VehicleType::TWO_WHEELER),
        new Vehicle("HR26-3333", VehicleType::FOUR_WHEELER),
        new Vehicle("HR26-4444", VehicleType::FOUR_WHEELER),
        new Vehicle("HR26-5555", VehicleType::FOUR_WHEELER)  // no four wheeler spot left for this one
    };

    std::cout << "--- Parking vehicles ---" << std::endl;
    std::vector<Ticket*> tickets;
    for(Vehicle* vehicle : vehicles){
        tickets.push_back(parkVehicle(parkingLot, vehicle));
    }

    std::cout << "\n--- Exiting a four wheeler (pays by UPI) ---" << std::endl;
    exitVehicle(parkingLot, tickets[2], &upiPayment);

    std::cout << "\n--- The turned away vehicle retries now that a spot is free ---" << std::endl;
    tickets[4] = parkVehicle(parkingLot, vehicles[4]);

    std::cout << "\n--- Exiting the rest (cash) ---" << std::endl;
    exitVehicle(parkingLot, tickets[0], &cashPayment);
    exitVehicle(parkingLot, tickets[1], &cashPayment);
    exitVehicle(parkingLot, tickets[3], &cashPayment);
    exitVehicle(parkingLot, tickets[4], &cashPayment);

    std::cout << "\n--- Re-exiting an already closed ticket is a no-op ---" << std::endl;
    exitVehicle(parkingLot, tickets[0], &cashPayment);

    for(Ticket* ticket : tickets) delete ticket;
    for(Vehicle* vehicle : vehicles) delete vehicle;

    return 0;
}
