/**
 * @file GreenhouseIterator.h
 * @brief Defines the GreenhouseIterator class, a concrete implementation of the Iterator pattern
 * for traversing a collection of Plant objects.
 */

#ifndef GREENHOUSE_ITERATOR_H
#define GREENHOUSE_ITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include <vector>

/**
 * @class GreenhouseIterator
 * @brief A concrete iterator that traverses all plants stored within the Greenhouse collection.
 *
 * This iterator provides a way to access the elements of the underlying collection
 * sequentially without exposing its internal representation.
 */


class GreenhouseIterator : public Iterator 
{
public:

    /**
     * @brief Constructor for the GreenhouseIterator.
     * @param plants A constant reference to the vector of Plant pointers to be iterated over.
     */

    explicit GreenhouseIterator(const std::vector<Plant*>& plants);

    /**
     * @brief Resets the iterator to the beginning of the collection.
     */
    
    void first() override;

    /**
     * @brief Advances the iterator to the next element in the collection.
     */
    
    void next() override;

    /**
     * @brief Checks if the iterator has moved past the last element in the collection.
     * @return true if iteration is complete, false otherwise.
     */
    
    bool isDone() const override;

    /**
     * @brief Retrieves the item (Plant pointer) at the current position of the iterator.
     * @return A pointer to the current Plant object.
     */
    
    Plant* currentItem() const override;

private:

    /**
     * @brief A copy of the collection (or a reference/pointer to it) being iterated over.
     */

    std::vector<Plant*> plants;

    /**
     * @brief The current position (index) within the `plants` vector.
     */
    
    size_t current;
};

#endif
