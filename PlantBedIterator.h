#ifndef PLANTBEDITERATOR_H
#define PLANTBEDITERATOR_H

#include "PlantIterator.h"
#include <cstddef>

class Bed;
class Plant;

/**
 * @class PlantBedIterator
 * @brief Concrete iterator for Bed that iterates over Plant* objects
 * 
 * Inherits from PlantIterator<Plant*> and implements iteration over plants in a Bed.
 */
class PlantBedIterator : public PlantIterator<Plant*> {
private:
    Bed& bed;
    size_t currentIndex;

public:
    /**
     * @brief Constructor
     * @param b Reference to Bed to iterate
     */
    PlantBedIterator(Bed& b);
    
    /**
     * @brief Destructor
     */
    ~PlantBedIterator();
    
    /**
     * @brief Get next plant
     * @return Reference to pointer to next Plant
     */
    Plant*& next() override;

    /**
     * @brief Check if there are more plants
     * @return True if has next, false otherwise
     */
    bool hasNext() override;
};

#endif // PLANTBEDITERATOR_H