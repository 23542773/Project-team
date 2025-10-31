#ifndef SPECIESCATALOG_H
#define SPECIESCATALOG_H
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "PlantFlyweight.h"

class SpeciesCatalog 
{

public:

    void add(std::shared_ptr<PlantFlyweight> fw);
    std::shared_ptr<PlantFlyweight> get(std::string sku);
    bool has(std::string sku);
    void remove(std::string sku);
    std::vector<std::shared_ptr<PlantFlyweight>> getAll() const;

private:
    std::unordered_map<std::string, std::shared_ptr<PlantFlyweight>> bySku;
};

#endif