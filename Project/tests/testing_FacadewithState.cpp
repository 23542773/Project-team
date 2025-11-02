#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <memory>

// --- Mock/Placeholder Forward Declarations ---
// Used by other classes, but not defined here
class PlantRegistry;
class PlantFlyweight;
class CareStrategy;
class SoilMix;
class Pot;
// ... (omitted other irrelevant mocks for brevity)


// =========================================================
// --- CORE MOCK IMPLEMENTATIONS TO FIX COMPILATION ---
// =========================================================

// --- MOCK 1: PlantState (Base Class) ---
class PlantState {
public:
    virtual ~PlantState() = default;
    virtual bool isMature() const { return false; } // Default is false
    // Required by Plant class
    virtual std::string name() const { return "Unknown"; }
};

// --- MOCK 2: MatureState (The "Available" State) ---
class MatureState : public PlantState {
private:
    MatureState() {} // Private constructor for Singleton
public:
    static MatureState* getInstance() {
        static MatureState instance;
        return &instance;
    }
    bool isMature() const override { return true; }
};

// --- MOCK 3: WiltingState (The "Unavailable" State) ---
class WiltingState : public PlantState {
private:
    WiltingState() {} // Private constructor for Singleton
public:
    static WiltingState* getInstance() {
        static WiltingState instance;
        return &instance;
    }
    bool isMature() const override { return false; } // Should return false
};

// --- MOCK 4: Plant (The Context Class) ---
class Plant {
private:
    std::string plantId;
    // Other attributes omitted for simplicity (color, flyweight, etc.)
    PlantState* currentState;

public:
    // Minimal constructor matching the 7 arguments used in the test
    Plant(std::string id, std::string colour, PlantFlyweight* sf, CareStrategy* cs,
          PlantState* initialState, SoilMix* sm, Pot* p)
        : plantId(id), currentState(initialState) {}
    
    // Required by the test and the Greenhouse mock
    std::string id() const { return plantId; } 

    // Required by the Facade mock for state check
    PlantState* getPlantState() const { return currentState; }

    // Required by the test for state change verification
    void setState(PlantState* newState) { currentState = newState; }
};

// =========================================================
// --- Original Test Classes (Now Fixed) ---
// =========================================================

// --- Simplified Mock Greenhouse Class for Test ---
class Greenhouse {
private:
    // FIX: Class name Plant is now defined
    std::unordered_map<std::string, Plant*> plantInstances; 
    PlantRegistry* proto = nullptr; 

public:
    Greenhouse(PlantRegistry* p) : proto(p) {} 
    
    void addPlant(Plant* plant) {
        plantInstances[plant->id()] = plant;
    }

    std::vector<Plant*> listAllPlants() {
        std::vector<Plant*> all;
        for (auto const& [id, plant] : plantInstances) {
            all.push_back(plant);
        }
        return all;
    }
};

// --- Simplified Mock Facade for Test ---
class NurseryFacadeTest {
private:
    Greenhouse* greenhouse = nullptr;
public:
    NurseryFacadeTest(Greenhouse* gh) : greenhouse(gh) {}

    std::vector<Plant*> browseAvailable() {
        std::vector<Plant*> availablePlants;
        std::vector<Plant*> allPlants = greenhouse->listAllPlants(); 

        for (Plant* p : allPlants) {
            // Relies on MatureState::isMature() returning true and others returning false.
            if (p->getPlantState()->isMature()) { 
                availablePlants.push_back(p);
            }
        }
        return availablePlants;
    }

    std::vector<Plant*> listAllPlants() {
        return greenhouse->listAllPlants();
    }
};

// =========================================================
// --- Test Execution Function ---
// =========================================================

void runStatePatternTest() {
    std::cout << "--- Running State Pattern & Facade Test ---" << std::endl;

    // Placeholders for dependencies required by Plant and Greenhouse
    PlantRegistry* mockRegistry = nullptr;
    PlantFlyweight* mockSpecies = nullptr;
    CareStrategy* mockCare = nullptr;
    SoilMix* mockSoil = nullptr;
    Pot* mockPot = nullptr;

    // 1. Setup: Initialize Greenhouse and Facade
    Greenhouse nursery(mockRegistry); 

    // Get the Singleton states (FIXED: Classes are now defined)
    PlantState* wilting = WiltingState::getInstance(); 
    PlantState* mature = MatureState::getInstance(); 
    
    // Create Plant objects using the full 7-argument constructor
    Plant p1("Rose_001", "Red", mockSpecies, mockCare, wilting, mockSoil, mockPot); 
    Plant p2("Lily_002", "White", mockSpecies, mockCare, mature, mockSoil, mockPot);   

    nursery.addPlant(&p1);
    nursery.addPlant(&p2);

    NurseryFacadeTest facade(&nursery); 
    
    // Initial check (Wilting plant should NOT be returned)
    std::cout << "\n--- Test Step 1: Initial Browse (p1=Wilting, p2=Mature) ---" << std::endl;
    std::vector<Plant*> available1 = facade.browseAvailable();

    std::cout << "Total Plants in Greenhouse (listAllPlants): " << facade.listAllPlants().size() << std::endl; 
    std::cout << "Plants Available (browseAvailable): " << available1.size() << std::endl;

    // Verification 1: Only p2 (Mature) should be available
    if (available1.size() == 1 && available1[0]->id() == "Lily_002") { 
        std::cout << " Verification 1 Passed: Only the Mature plant was returned." << std::endl;
    } else {
        std::cout << " Verification 1 FAILED: Expected 1 Mature plant, got " << available1.size() << "." << std::endl;
        // Search for "Rose_001" to confirm it's not present
        bool found_p1 = (std::find_if(available1.begin(), available1.end(), 
                        [](Plant* p){ return p->id() == "Rose_001"; }) != available1.end());
        if (found_p1) std::cout << "Error: Wilting plant was incorrectly included." << std::endl;
    }

    // 2. State Change: Plant 1 transitions from Wilting to Mature
    p1.setState(mature);
    std::cout << "\nSimulating state transition: " << p1.id() << " -> Matured" << std::endl;

    // 3. Final check (BOTH plants should now be returned)
    std::cout << "\n--- Test Step 2: Final Browse (p1=Mature, p2=Mature) ---" << std::endl;
    std::vector<Plant*> available2 = facade.browseAvailable();

    std::cout << "Total Plants in Greenhouse (listAllPlants): " << facade.listAllPlants().size() << std::endl; 
    std::cout << "Plants Available (browseAvailable): " << available2.size() << std::endl;
    
    // Verification 2: Both p1 and p2 should be available
    if (available2.size() == 2) {
        std::cout << " Verification 2 Passed: Both plants are now Mature and available." << std::endl;
    } else {
        std::cout << " Verification 2 FAILED: Expected 2 Mature plants, got " << available2.size() << "." << std::endl;
    }
    std::cout << "\n--- Test Complete ---" << std::endl;
}

 int main() {
     runStatePatternTest();
     return 0;
 }