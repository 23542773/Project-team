/**
 * @file DeadState.h
 * @brief Defines the DeadState concrete state class
 */

#ifndef DEADSTATE_H
#define DEADSTATE_H
#include "PlantState.h"
#include "SingletonState.h"

/**
 * @class DeadState
 * @brief Concrete State class representing a dead plant that cannot recover
 *
 * This state represents the terminal state in a plant's lifecycle. Once a plant
 * enters this state, it cannot transition to any other state. The plant has
 * reached zero or negative health and is no longer viable.
 */
class DeadState : public SingletonState<DeadState>
{
public:
	/**
	 * @brief Checks plant conditions (no state changes possible from Dead state)
	 * @param plant Reference to the Plant object (unused in this state)
	 *
	 * This is a terminal state with no possible transitions, so this method
	 * performs no operations.
	 */
    void checkChange(Plant& plant) override;

	/**
	 * @brief Gets the name of this state
	 * @return String "Dead"
	 */
    std::string name() override;

private:
	/**
	 * @brief Friend declaration to allow SingletonState access to constructor
	 */
    friend class SingletonState<DeadState>;

	/**
	 * @brief Private default constructor (singleton pattern)
	 */
    DeadState() = default;
};

#endif
