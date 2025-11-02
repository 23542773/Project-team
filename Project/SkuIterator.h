/**
 * @file SkuIterator.h
 * @brief Defines the SkuIterator class, a concrete Iterator for traversing Plant objects
 * that match a specific species SKU.
 */

#ifndef SKU_ITERATOR_H
#define SKU_ITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include <vector>
#include <string>

/**
 * @class SkuIterator
 * @brief A concrete iterator designed to skip over elements and only yield Plant objects
 * whose species Stock Keeping Unit (SKU) matches a predefined target.
 *
 * This iterator hides the complexity of filtering the underlying collection from the client.
 */

class SkuIterator : public Iterator 
{
public:

    /**
     * @brief Constructor for the SkuIterator.
     * @param plants A constant reference to the vector of Plant pointers to be iterated over.
     * @param sku The target SKU to filter the plants by.
     */

    SkuIterator(const std::vector<Plant*>& plants, const std::string& sku);

    /**
     * @brief Resets the iterator to the beginning of the collection and advances to the first matching plant.
     */
    
    void first() override;

    /**
     * @brief Advances the iterator past the current plant to the next plant that matches the target SKU.
     */
    
    void next() override;

    /**
     * @brief Checks if the iterator has moved past the last matching element in the collection.
     * @return true if iteration is complete, false otherwise.
     */
    
    bool isDone() const override;

    /**
     * @brief Retrieves the item (Plant pointer) at the current, matching position of the iterator.
     * @return A pointer to the current Plant object, or nullptr if `isDone()` is true.
     */
    
    Plant* currentItem() const override;

private:

/**
 * @brief Private helper function to move the internal cursor (`current`) forward until it finds a Plant
 * that matches the `targetSku` or reaches the end of the collection.
 */

    void advanceToMatch();

    /**
     * @brief A copy of the collection (or a reference/pointer to it) being iterated and filtered over.
     */

    std::vector<Plant*> plants;

    /**
     * @brief The specific SKU that plants must match to be yielded by the iterator.
     */

    std::string targetSku;

    /**
     * @brief The current position (index) within the `plants` vector.
     */
    
    size_t current;
};

#endif
