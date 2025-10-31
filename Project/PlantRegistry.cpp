#include "PlantRegistry.h"

void PlantRegistry::registerSeedling(std::string sku, std::unique_ptr<Plant> p) 
{
    bySku[sku] = std::move(p);
}

Plant* PlantRegistry::clone(std::string sku, std::string newId, std::string colour) 
{
    auto it = bySku.find(sku);
    if (it == bySku.end()) 
    {
        std::cerr << "SKU not found\n";
        return nullptr;
    }
    if (!it->second) 
    {
        std::cerr << "Registry entry is null for " << sku << "\n";
        return nullptr;
    }
    return it->second->clone(newId, colour);
}

bool PlantRegistry::has(std::string sku) 
{ 
    return bySku.count(sku) != 0; 
}