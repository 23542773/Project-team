#ifndef PLANTREGISTRY_H
#define PLANTREGISTRY_H
#include <unordered_map>
#include <memory>
#include <string>
#include "Plant.h"

class PlantRegistry 
{
public:

    void registerSeedling(std::string sku, std::unique_ptr<Plant> p);
    Plant* clone(std::string sku, std::string newId, std::string colour);
    bool has(std::string sku);

private:

    std::unordered_map<std::string, std::unique_ptr<Plant>> bySku;
};

#endif