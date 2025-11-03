/**
 * @file PlantState.h
 * @brief Defines the abstract base State interface for the State pattern
 */


#ifndef PLANTSTATE_H
#define PLANTSTATE_H
#include <string>

class Plant;

/**
 * @class PlantState
 * @brief Abstract State class in the State pattern representing different plant growth states
 *
 * This class defines the interface for all concrete plant states. Each state encapsulates
 * the behavior associated with a particular stage of a plant's lifecycle and determines
 * transitions to other states based on plant health, moisture, insecticide levels, and age.
 */

class PlantState 
{

public:

    /**
	 * @brief Virtual destructor for proper cleanup of derived state classes
	 */
	virtual ~PlantState() = default;

    /**
	 * @brief Checks and potentially changes the plant's state based on current conditions
	 * @param plant Reference to the Plant object whose state is being managed
	 *
	 * This method evaluates the plant's current attributes (health, moisture, insecticide, age)
	 * and transitions to an appropriate state if conditions warrant a change.
	 */
    virtual void checkChange(Plant& plant) = 0;

    /**
	 * @brief Gets the name of the current state
	 * @return String representing the state name
	 */
    virtual std::string name() = 0;

    /**
	 * @brief Checks if the plant is in a mature state
	 * @return True if the state represents maturity, false otherwise (default)
	 */
    virtual bool isMature() { return false; }
};
#endif
