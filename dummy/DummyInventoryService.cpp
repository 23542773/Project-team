#include "DummyInventoryService.h"
#include "DummyPlant.h"
#include <iostream>

DummyInventoryService::DummyInventoryService() {
    std::cout << "[DummyInventoryService] Initializing with hardcoded stock...\n";
    
    // TODO: Populate with dummy stock
    stock["SUCC-001"] = 15;  // Aloe Vera
    stock["CACT-001"] = 8;   // Desert Rose
    stock["ORCH-001"] = 3;   // Orchid
    stock["HERB-023"] = 20;  // Lavender
    stock["FERN-005"] = 5;   // Boston Fern
    
    std::cout << "[DummyInventoryService] Loaded " << stock.size() << " SKUs\n";
    for (const auto& pair : stock) {
        std::cout << "  - " << pair.first << ": " << pair.second << " units\n";
    }
}

DummyInventoryService::~DummyInventoryService() {
    // TODO: Cleanup plants if needed
    for (auto& pair : plants) {
        delete pair.second;
    }
    plants.clear();
}

void DummyInventoryService::add(const std::string& sku, int qty) {
    stock[sku] += qty;
    std::cout << "[DummyInventoryService] Added " << qty << " units of " << sku 
              << " (now: " << stock[sku] << ")\n";
}

bool DummyInventoryService::remove(const std::string& sku, int qty) {
    if (available(sku) >= qty) {
        stock[sku] -= qty;
        std::cout << "[DummyInventoryService] Removed " << qty << " units of " << sku 
                  << " (now: " << stock[sku] << ")\n";
        return true;
    }
    std::cout << "[DummyInventoryService] FAILED to remove " << qty << " units of " << sku 
              << " (only " << available(sku) << " available)\n";
    return false;
}

int DummyInventoryService::available(const std::string& sku) const {
    auto it = stock.find(sku);
    if (it != stock.end()) {
        return it->second;
    }
    return 0;
}

void DummyInventoryService::restock(const std::string& sku, int qty) {
    add(sku, qty);
}

bool DummyInventoryService::consume(const std::string& sku, int qty) {
    return remove(sku, qty);
}

void DummyInventoryService::addPlant(const std::string& sku, DummyPlant* plant) {
    if (plant) {
        plants[sku] = plant;
        std::cout << "[DummyInventoryService] Stored plant: " << sku << "\n";
    }
}

DummyPlant* DummyInventoryService::getPlant(const std::string& sku) const {
    auto it = plants.find(sku);
    if (it != plants.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<DummyPlant*> DummyInventoryService::getAllPlants() const {
    std::vector<DummyPlant*> result;
    for (const auto& pair : plants) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<std::string> DummyInventoryService::getAllSKUs() const {
    std::vector<std::string> skus;
    for (const auto& pair : stock) {
        skus.push_back(pair.first);
    }
    return skus;
}