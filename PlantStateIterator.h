#ifndef PLANTSTATEITERATOR_H
#define PLANTSTATEITERATOR_H

#include "PlantIterator.h"
#include "Greenhouse.h"
#include "Plant.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

class Greenhouse;

/**
 * @class PlantStateIterator
 * @brief Iterator for traversing all plants across all beds in a greenhouse.
 * 
 * This iterator flattens the hierarchical structure of greenhouse->beds->plants
 * into a sequential collection for easy iteration.
 */
class PlantStateIterator : public PlantIterator<Plant*> {
private:
    std::vector<Plant*> allPlants; ///< Flattened collection of all plants
    size_t current; ///< Current position in the iteration

public:
    /**
     * @brief Constructs an iterator for the given greenhouse.
     * @param gh The Greenhouse to iterate over.
     */
    explicit PlantStateIterator(const Greenhouse& gh);
        
    /**
     * @brief Checks if there are more plants to iterate over.
     * @return true if there are more plants, false otherwise.
     */
    bool hasNext() const override;
    
    /**
     * @brief Returns the next plant in the iteration.
     * @return Reference to a pointer to the next Plant.
     * @throws std::out_of_range if there are no more plants.
     */
    Plant*& next() override;
    
    /**
     * @brief Resets the iterator to the beginning.
     */
    void reset() override;
    
    /**
     * @brief Moves the iterator to a specific position.
     * @param index The position to move to.
     * @throws std::out_of_range if index is out of bounds.
     */
    void goTo(size_t index) override;
    
    /**
     * @brief Returns the current position of the iterator.
     * @return The current index in the iteration.
     */
    size_t currentIndex() const override;
};

#endif