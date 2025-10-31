/**
 * @file SpeciesCatalog.cpp
 * @brief Implementation of the SpeciesCatalog flyweight factory
 */

#include "SpeciesCatalog.h"

/**
 * @brief Adds a flyweight to the catalog
 *
 * This method stores the flyweight in the internal map if it's valid.
 * The flyweight is indexed by its SKU for efficient retrieval.
 */
void SpeciesCatalog::add(std::shared_ptr<PlantFlyweight> fw)
{
    if (fw) bySku[fw->getSku()] = std::move(fw);
}

/**
 * @brief Retrieves a flyweight from the catalog by SKU
 *
 * Searches the catalog for a flyweight with the specified SKU.
 * Returns nullptr if no matching flyweight is found.
 */
std::shared_ptr<PlantFlyweight> SpeciesCatalog::get(std::string sku)
{
    auto it = bySku.find(sku);
    return (it == bySku.end()) ? nullptr : it->second;
}

/**
 * @brief Checks if a flyweight with the given SKU exists in the catalog
 *
 * Performs a lookup to determine if the catalog contains a flyweight
 * with the specified SKU identifier.
 */
bool SpeciesCatalog::has(std::string sku)
{
    return bySku.find(sku) != bySku.end();
}

/**
 * @brief Removes a flyweight from the catalog
 *
 * Erases the flyweight with the specified SKU from the catalog.
 * If the SKU doesn't exist, this operation has no effect.
 */
void SpeciesCatalog::remove(std::string sku)
{
	bySku.erase(sku);
}

/**
 * @brief Retrieves all flyweights stored in the catalog
 *
 * Creates and returns a vector containing all flyweights currently
 * stored in the catalog. The vector is pre-allocated for efficiency.
 */
std::vector<std::shared_ptr<PlantFlyweight>> SpeciesCatalog::getAll() const
{
    std::vector<std::shared_ptr<PlantFlyweight>> out;
    out.reserve(bySku.size());
    for (const auto& [_, fw] : bySku)
        out.push_back(fw);
    return out;
}