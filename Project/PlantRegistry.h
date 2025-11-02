/**
 * @file PlantRegistry.h
 * @brief Defines the PlantRegistry class, which manages prototype Plant objects for cloning (Prototype Pattern).
 */

#ifndef PLANTREGISTRY_H
#define PLANTREGISTRY_H
#include <unordered_map>
#include <memory>
#include <string>
#include "Plant.h"

/**
 * @class PlantRegistry
 * @brief Manages a collection of unique prototype Plant objects, keyed by their SKU.
 *
 * This class serves as the **Prototype Registry**, allowing clients (like the Greenhouse)
 * to retrieve and clone new Plant instances without needing to know the complex creation
 * logic of the concrete Plant classes.
 */

class PlantRegistry 
{
public:

/**
 * @brief Registers a prototype Plant object under a specific Species SKU.
 *
 * The registry takes ownership of the provided unique pointer.
 *
 * @param sku The Stock Keeping Unit to use as the key for the prototype.
 * @param p A unique pointer to the Plant object (the prototype) to be stored.
 */

    void registerSeedling(std::string sku, std::unique_ptr<Plant> p);
    /**
     * @brief Creates a new Plant instance by cloning the registered prototype for the given SKU.
     *
     * The new instance is initialized with a unique ID and a color.
     *
     * @param sku The Stock Keeping Unit of the prototype to clone.
     * @param newId The unique identifier to assign to the new cloned Plant instance.
     * @param colour The color string to assign to the new cloned Plant instance.
     * @return A raw pointer to the newly created and initialized Plant instance, or nullptr if the SKU is not registered.
     */

    Plant* clone(std::string sku, std::string newId, std::string colour);

    /**
     * @brief Checks if a prototype Plant is registered under the given SKU.
     * @param sku The Stock Keeping Unit to check.
     * @return true if a prototype exists for the SKU, false otherwise.
     */

    bool has(std::string sku);

private:

/**
 * @brief The map storing the prototype Plant objects, keyed by species SKU.
 * Unique pointers ensure proper ownership and memory management of the prototypes.
 */

    std::unordered_map<std::string, std::unique_ptr<Plant>> bySku;
};

#endif