#include "DummyPlantKitFactory.h"
#include "DummyPlant.h"
#include "DummyPlantFlyweight.h"
#include "DummyPlantState.h"
#include <iostream>

DummyPlantKitFactory::DummyPlantKitFactory(const std::string& environment)
    : envType(environment) {
    std::cout << "[DummyPlantKitFactory] Created factory for: " << environment << "\n";
}

DummyPlant* DummyPlantKitFactory::createPlant(const std::string& id,
                                             DummyPlantFlyweight* species) {
    std::cout << "[DummyPlantKitFactory] Creating plant: " << id << "\n";
    
    // TODO: Create in MATURE state by default for testing
    DummyPlantState* state = new DummyMatureState();
    DummyPlant* plant = new DummyPlant(id, species, state);
    
    return plant;
}

DummyPot* DummyPlantKitFactory::createPot() {
    std::string potName;
    
    if (envType == "Indoor") {
        potName = "Ceramic Pot";
    } else if (envType == "Desert") {
        potName = "Terracotta Pot";
    } else if (envType == "Tropical") {
        potName = "Glazed Ceramic Pot";
    } else if (envType == "Wetland") {
        potName = "Aquatic Basket Pot";
    } else {
        potName = "Generic Pot";
    }
    
    std::cout << "[DummyPlantKitFactory] Creating pot: " << potName << "\n";
    return new DummyPot(potName);
}

DummySoilMix* DummyPlantKitFactory::createSoilMix() {
    std::string soilName;
    
    if (envType == "Indoor") {
        soilName = "Light Airy Soil";
    } else if (envType == "Desert") {
        soilName = "Sandy Soil";
    } else if (envType == "Tropical") {
        soilName = "Peat Soil";
    } else if (envType == "Wetland") {
        soilName = "Aquatic Soil";
    } else {
        soilName = "Generic Soil";
    }
    
    std::cout << "[DummyPlantKitFactory] Creating soil: " << soilName << "\n";
    return new DummySoilMix(soilName);
}

std::string DummyPlantKitFactory::getEnvironmentType() const {
    return envType;
}