/**
 * @file SpeciesCatalog.h
 * @brief Defines the Flyweight Factory for managing plant species flyweights
 */

#ifndef SPECIESCATALOG_H
#define SPECIESCATALOG_H
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "PlantFlyweight.h"

/**
 * @class SpeciesCatalog
 * @brief Flyweight Factory that manages and provides access to PlantFlyweight objects
 *
 * This class implements the Flyweight Factory pattern, maintaining a pool of shared
 * flyweight objects to minimize memory usage. It ensures that flyweights are shared
 * properly by managing their lifecycle and providing access through unique SKU identifiers.
 */
class SpeciesCatalog
{

public:

    /**
     * @brief Adds a flyweight to the catalog
     * @param fw Shared pointer to the PlantFlyweight object to add
     *
     * If the flyweight pointer is valid, it will be stored in the catalog
     * indexed by its SKU identifier.
     */
    void add(std::shared_ptr<PlantFlyweight> fw);

    /**
     * @brief Retrieves a flyweight from the catalog by SKU
     * @param sku The SKU identifier of the plant species to retrieve
     * @return Shared pointer to the PlantFlyweight if found, nullptr otherwise
     */
    std::shared_ptr<PlantFlyweight> get(std::string sku);

    /**
     * @brief Checks if a flyweight with the given SKU exists in the catalog
     * @param sku The SKU identifier to check
     * @return true if the flyweight exists, false otherwise
     */
    bool has(std::string sku);

    /**
     * @brief Removes a flyweight from the catalog
     * @param sku The SKU identifier of the plant species to remove
     */
    void remove(std::string sku);

    /**
     * @brief Retrieves all flyweights stored in the catalog
     * @return Vector containing shared pointers to all PlantFlyweight objects
     */
    std::vector<std::shared_ptr<PlantFlyweight>> getAll() const;

private:
    /**
     * @brief Map storing flyweights indexed by their SKU identifiers
     */
    std::unordered_map<std::string, std::shared_ptr<PlantFlyweight>> bySku;
};

#endif