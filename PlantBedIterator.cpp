/**
 * @file PlantBedIterator.cpp
 * @brief Implementation of the PlantBedIterator class for iterating over plants in a bed
 */

#include "PlantBedIterator.h"
#include "Bed.h"

/**
 * @brief Constructs a PlantBedIterator for the given bed
 * @param bed The bed to iterate over
 */
PlantBedIterator::PlantBedIterator(Bed& bed) 
    : plants(bed.getPlants()), current(0) 
{
}

/**
 * @brief Checks if there are more plants to iterate over
 * @return true if there are more plants, false otherwise
 */
bool PlantBedIterator::hasNext() const {
    return current < plants.size();
}

/**
 * @brief Returns the next plant in the iteration
 * @return Reference to a pointer to the next Plant
 */
Plant*& PlantBedIterator::next() {
    if (!hasNext()) throw std::out_of_range("No more plants in bed");
    return plants[current++];
}

/**
 * @brief Resets the iterator to the beginning
 */
void PlantBedIterator::reset() {
    current = 0;
}

/**
 * @brief Moves the iterator to a specific position
 * @param index The position to move to
 */
void PlantBedIterator::goTo(size_t index) {
    if (index >= plants.size()) throw std::out_of_range("Index out of range");
    current = index;
}

/**
 * @brief Returns the current position of the iterator
 * @return The current index in the iteration
 */
size_t PlantBedIterator::currentIndex() const {
    return current;
}