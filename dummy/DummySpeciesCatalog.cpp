#include "DummySpeciesCatalog.h"
#include "DummyPlantFlyweight.h"
#include <iostream>

DummySpeciesCatalog::DummySpeciesCatalog() {
    std::cout << "[DummySpeciesCatalog] Initializing hardcoded species...\n";
    
    // TODO: Populate with dummy species
    speciesPool["SUCC-001"] = new DummyPlantFlyweight("aloe");
    speciesPool["CACT-001"] = new DummyPlantFlyweight("cactus");
    speciesPool["ORCH-001"] = new DummyPlantFlyweight("orchid");
    speciesPool["HERB-023"] = new DummyPlantFlyweight("lavender");
    speciesPool["FERN-005"] = new DummyPlantFlyweight("fern");
    
    std::cout << "[DummySpeciesCatalog] Loaded " << speciesPool.size() << " species\n";
}

DummySpeciesCatalog::~DummySpeciesCatalog() {
    // TODO: Cleanup
    for (auto& pair : speciesPool) {
        delete pair.second;
    }
    speciesPool.clear();
}

DummyPlantFlyweight* DummySpeciesCatalog::getBySKU(const std::string& sku) const {
    auto it = speciesPool.find(sku);
    if (it != speciesPool.end()) {
        return it->second;
    }
    return nullptr;
}

void DummySpeciesCatalog::registerSpecies(const std::string& sku, 
                                         DummyPlantFlyweight* species) {
    if (species) {
        speciesPool[sku] = species;
    }
}

bool DummySpeciesCatalog::hasSKU(const std::string& sku) const {
    return speciesPool.find(sku) != speciesPool.end();
}

std::vector<std::string> DummySpeciesCatalog::getAllSKUs() const {
    std::vector<std::string> skus;
    for (const auto& pair : speciesPool) {
        skus.push_back(pair.first);
    }
    return skus;
}

std::string DummySpeciesCatalog::getSpeciesName(const std::string& sku) const {
    DummyPlantFlyweight* species = getBySKU(sku);
    if (species) {
        return species->speciesName();
    }
    return "";
}

std::string DummySpeciesCatalog::getEnvironmentType(const std::string& sku) const {
    DummyPlantFlyweight* species = getBySKU(sku);
    if (species) {
        return species->envType();
    }
    return "";
}