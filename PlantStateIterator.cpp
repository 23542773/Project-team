/**
 * @file PlantStateIterator.cpp
 * @brief Implementation of the PlantStateIterator class for iterating over all plants in a greenhouse.
 */

#include "PlantStateIterator.h"
#include "Greenhouse.h"

/**
 * @brief Constructs a PlantStateIterator for the given greenhouse.
 * @param gh The Greenhouse to iterate over.
 */
PlantStateIterator::PlantStateIterator(const Greenhouse& gh) : current(0) {
    // Flatten all plants from all beds
    for (auto* bed : gh.getBeds()) {
        for (auto* plant : bed->getPlants()) {
            allPlants.push_back(plant);
        }
    }
}

/**
 * @brief Checks if there are more plants to iterate over.
 * @return true if there are more plants, false otherwise.
 */
bool PlantStateIterator::hasNext() const {
    return current < allPlants.size();
}

/**
 * @brief Returns the next plant in the iteration.
 * @return Reference to a pointer to the next Plant.
 * @throws std::out_of_range if there are no more plants.
 */
Plant*& PlantStateIterator::next() {
    if (!hasNext()) throw std::out_of_range("No more plants");
    return allPlants[current++];
}

/**
 * @brief Resets the iterator to the beginning.
 */
void PlantStateIterator::reset() {
    current = 0;
}

/**
 * @brief Moves the iterator to a specific position.
 * @param index The position to move to.
 * @throws std::out_of_range if index is out of bounds.
 */
void PlantStateIterator::goTo(size_t index) {
    if (index >= allPlants.size()) throw std::out_of_range("Index out of range");
    current = index;
}

/**
 * @brief Returns the current position of the iterator.
 * @return The current index in the iteration.
 */
size_t PlantStateIterator::currentIndex() const {
    return current;
}