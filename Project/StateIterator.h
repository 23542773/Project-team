/**
 * @file StateIterator.h
 * @brief Defines the StateIterator class, a concrete Iterator for traversing Plant objects
 * that are currently in a specific state (State Pattern integration).
 */

#ifndef STATE_ITERATOR_H
#define STATE_ITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include "PlantState.h"
#include <vector>

/**
 * @class StateIterator
 * @brief A concrete iterator designed to skip over elements and only yield Plant objects
 * whose internal state pointer matches a predefined target PlantState.
 *
 * This iterator provides a filtered view of the Greenhouse collection, focused on plants
 * sharing a specific lifecycle state (e.g., only "MatureState" plants).
 */

class StateIterator : public Iterator 
{
public:

    /**
     * @brief Constructor for the StateIterator.
     * @param plants A constant reference to the vector of Plant pointers to be iterated over.
     * @param state A pointer to the target PlantState object to filter the plants by.
     */

    StateIterator(const std::vector<Plant*>& plants, const PlantState* state);

    /**
     * @brief Resets the iterator to the beginning of the collection and advances to the first matching plant.
     */
    
    void first() override;

    /**
     * @brief Advances the iterator past the current plant to the next plant that matches the target state.
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
     * whose state matches the `targetState` or reaches the end of the collection.
     */

    void advanceToMatch();

    /**
     * @brief A copy of the collection (or a reference/pointer to it) being iterated and filtered over.
     */

    std::vector<Plant*> plants;

    /**
     * @brief A pointer to the specific PlantState object that plants must match to be yielded by the iterator.
     */

    const PlantState* targetState;

    /**
     * @brief The current position (index) within the `plants` vector.
     */
    
    size_t current;
};

#endif
