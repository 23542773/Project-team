/**
 * @file FlyweightSKUIterator.cpp
 * @brief Implementation of the FlyweightSKUIterator class for iterating over species catalog entries.
 */

#include "FlyweightSKUIterator.h"
#include <stdexcept>

/**
 * @brief Constructs a FlyweightSKUIterator for the given species catalog.
 * @param catalog The SpeciesCatalog to iterate over.
 */
FlyweightSKUIterator::FlyweightSKUIterator(const SpeciesCatalog& catalog)
    : current(0)
{
    // copy all pairs from the catalog
    for (const auto& entry : catalog.bySku) {
        entries.push_back(entry);
    }
}

/**
 * @brief Checks if there are more elements to iterate over.
 * @return true if there are more elements, false otherwise.
 */
bool FlyweightSKUIterator::hasNext() const {
    return current < entries.size();
}

/**
 * @brief Returns the next element in the iteration.
 * @return A pair containing the SKU and corresponding PlantFlyweight.
 * @throws std::out_of_range if there are no more elements.
 */
std::pair<std::string, std::shared_ptr<PlantFlyweight>> FlyweightSKUIterator::next() {
    if (!hasNext()) throw std::out_of_range("No more SKUs in catalog");
    return entries[current++];
}

/**
 * @brief Resets the iterator to the beginning.
 */
void FlyweightSKUIterator::reset() {
    current = 0;
}