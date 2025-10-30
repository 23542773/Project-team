#ifndef SPECIESCATALOG_H
#define SPECIESCATALOG_H
#include <memory>
#include <unordered_map>
#include <string>
#include "PlantFlyweight.h"

class FlyweightSKUIterator;

/**
 * @class SpeciesCatalog
 * @brief Flyweight factory for managing shared plant species
 */
class SpeciesCatalog 
{

    friend class FlyweightSKUIterator;

public:

    void add(std::shared_ptr<PlantFlyweight> fw);
    std::shared_ptr<PlantFlyweight> get(std::string sku);
    bool has(std::string sku);
    void remove(std::string sku);

private:
    std::unordered_map<std::string, std::shared_ptr<PlantFlyweight>> bySku;
};

#endif