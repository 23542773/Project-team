#ifndef FLYWEIGHTSKUITERATOR_H
#define FLYWEIGHTSKUITERATOR_H

#include <vector>
#include <utility>
#include <string>
#include <memory>
#include "PlantFlyweight.h"
#include "SpeciesCatalog.h"
#include <stdexcept>

/**
 * @class FlyweightSKUIterator
 * @brief Iterator for traversing species catalog entries by SKU.
 * 
 * This iterator provides sequential access to all SKU-flyweight pairs
 * in a SpeciesCatalog.
 */
class FlyweightSKUIterator {
private:
    std::vector<std::pair<std::string, std::shared_ptr<PlantFlyweight>>> entries; ///< Collection of catalog entries
    size_t current; ///< Current position in the iteration

public:
    /**
     * @brief Constructs an iterator for the given catalog.
     * @param catalog The SpeciesCatalog to iterate over.
     */
    explicit FlyweightSKUIterator(const SpeciesCatalog& catalog);
    
    /**
     * @brief Checks if there are more elements to iterate over.
     * @return true if there are more elements, false otherwise.
     */
    bool hasNext() const;
    
    /**
     * @brief Returns the next element in the iteration.
     * @return A pair containing the SKU and corresponding PlantFlyweight.
     * @throws std::out_of_range if there are no more elements.
     */
    std::pair<std::string, std::shared_ptr<PlantFlyweight>> next();
    
    /**
     * @brief Resets the iterator to the beginning.
     */
    void reset();
};

#endif