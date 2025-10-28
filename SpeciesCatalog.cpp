#include "SpeciesCatalog.h"

void SpeciesCatalog::add(std::shared_ptr<PlantFlyweight> fw) { if (fw) bySku[fw->getSku()] = std::move(fw); }

std::shared_ptr<PlantFlyweight> SpeciesCatalog::get(std::string sku)  
{
    auto it = bySku.find(sku);
    return (it == bySku.end()) ? nullptr : it->second;
}

bool SpeciesCatalog::has(std::string sku) { return bySku.find(sku) != bySku.end(); }

void SpeciesCatalog::remove(std::string sku) { bySku.erase(sku); }