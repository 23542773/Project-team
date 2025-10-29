#include <iostream>
#include <cassert>
#include "Plant.h"
#include "SeedlingState.h"
#include "GrowingState.h"
#include "MatureState.h"
#include "WiltingState.h"
#include "DeadState.h"
#include "PlantFlyweight.h"
#include "CareStrategy.h"
#include "SoilMix.h"
#include "Pot.h"
#include "PlantState.h"

using namespace std;

// ======================================================
//   SIMPLE TEST IMPLEMENTATIONS FOR REQUIRED CLASSES
// ======================================================

// Flyweight
class SimpleFlyweight : public PlantFlyweight {
public:
    string getSku() const override { return "PLT-001"; }
    string getName() const override { return "Desert Rose"; }
    string getBiome() const override { return "Desert"; }
    int getCost()  override { return 50; }
};

// Soil
class SimpleSoil : public SoilMix {
public:
    SimpleSoil() : SoilMix(10) {}
    string name() const override { return "Standard Soil"; }
    SoilMix* clone() const override { return new SimpleSoil(*this); }
};

// Pot
class SimplePot : public Pot {
public:
    SimplePot() : Pot(20) {}
    string name() const override { return "Clay Pot"; }
    Pot* clone()  override { return new SimplePot(*this); }
};

// Care Strategy
class SimpleCare : public CareStrategy {
public:
    void water(Plant& p) override { p.addWater(25); }
    void fertilize(Plant& p) override { p.addHealth(10); }
};

// ======================================================
//                   HELPER FUNCTION
// ======================================================
void printStatus(const Plant& p) {
    cout << "Day " << p.getAgeDays()
         << " | State: " << p.getPlantState()->name()
         << " | Health: " << p.getHealth()
         << " | Moisture: " << p.getMoisture()
         << endl;
}

// ======================================================
//                STATE PATTERN TESTS
// ======================================================
void testStatePattern() {
    cout << "========== STATE PATTERN TEST ==========" << endl;

    SimpleFlyweight species;
    SimpleSoil soil;
    SimplePot pot;
    SimpleCare care;

    // Start with a Seedling
    Plant plant("P001", "Green", &species, &care, &SeedlingState::getInstance(), &soil, &pot);
    plant.addHealth(50);
    plant.addWater(70);

    // ----------------- SEEDLING → GROWING -----------------
    cout << "\n-- Testing Seedling → Growing Transition --" << endl;
    for (int i = 0; i < 6; ++i) {
        plant.tickDay();
        printStatus(plant);
    }
    assert(plant.getPlantState() == &GrowingState::getInstance());
    cout << "✅ Reached GrowingState\n";

    // ----------------- GROWING → MATURE -----------------
    cout << "\n-- Testing Growing → Mature Transition --" << endl;
    for (int i = 0; i < 10; ++i) {
        plant.addHealth(5);  // ensure good condition
        plant.tickDay();
        printStatus(plant);
    }
    assert(plant.getPlantState() == &MatureState::getInstance());
    cout << "✅ Reached MatureState\n";

    // ----------------- MATURE → WILTING -----------------
    cout << "\n-- Testing Mature → Wilting Transition --" << endl;
    plant.addWater(-80); // dehydrate the plant
    for (int i = 0; i < 3; ++i) {
        plant.tickDay();
        printStatus(plant);
    }
    assert(plant.getPlantState() == &WiltingState::getInstance());
    cout << "✅ Reached WiltingState\n";

    // ----------------- WILTING → DEAD -----------------
    cout << "\n-- Testing Wilting → Dead Transition --" << endl;
    for (int i = 0; i < 10; ++i) {
        plant.tickDay();
        printStatus(plant);
    }
    assert(plant.getPlantState() == &DeadState::getInstance());
    cout << "✅ Reached DeadState\n";

    cout << "\n========== STATE PATTERN TEST COMPLETE ==========\n" << endl;
}

// ======================================================
//                       MAIN
// ======================================================
int main() {
    testStatePattern();
    return 0;
}
