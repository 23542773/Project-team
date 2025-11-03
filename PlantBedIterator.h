/**
 * @file PlantBedIterator.h
 * @brief Iterator for iterating over plants in a single bed
 */

#ifndef PLANTBEDITERATOR_H
#define PLANTBEDITERATOR_H

#include "PlantIterator.h"
#include "Bed.h"
#include "Plant.h"
#include <vector>
#include <stdexcept>

class Bed;

/**
 * @class PlantBedIterator
 * @brief Iterator for traversing plants within a single bed
 * 
 * Provides sequential access to all plants in a specific bed.
 */
class PlantBedIterator : public PlantIterator<Plant*> {
private:
    std::vector<Plant*>& plants; ///< Reference to the plants vector from the bed
    size_t current; ///< Current position in the iteration

public:
    /**
     * @brief Constructs an iterator for the given bed
     * @param bed The bed to iterate over
     */
    explicit PlantBedIterator(Bed& bed);

    /**
     * @brief Checks if there are more plants to iterate over
     * @return true if there are more plants, false otherwise
     */
    bool hasNext() const override;
    
    /**
     * @brief Returns the next plant in the iteration
     * @return Reference to a pointer to the next Plant
     */
    Plant*& next() override;
    
    /**
     * @brief Resets the iterator to the beginning
     */
    void reset() override;
    
    /**
     * @brief Moves the iterator to a specific position
     * @param index The position to move to
     */
    void goTo(size_t index) override;
    
    /**
     * @brief Returns the current position of the iterator
     * @return The current index in the iteration
     */
    size_t currentIndex() const override;
};

#endif
