/**
 * @file SeedlingState.h
 * @brief Defines the SeedlingState concrete state class
 */

#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H
#include "PlantState.h"
#include "SingletonState.h"

/**
 * @class SeedlingState
 * @brief Concrete State class representing a young plant in its early growth stage
 *
 * This state represents the initial viable growth stage of a plant after germination.
 * Seedlings have moderate resource consumption and are vulnerable to poor conditions.
 * Can transition to GrowingState when age and health thresholds are met, or to
 * DeadState if health drops to zero.
 */
class SeedlingState : public SingletonState<SeedlingState>
{
public:
	/**
	 * @brief Evaluates plant conditions and manages state transitions
	 * @param plant Reference to the Plant object being evaluated
	 *
	 * Decrements water and insecticide levels, adjusts health based on care conditions,
	 * and transitions to GrowingState or DeadState based on age, health, and species
	 * characteristics.
	 */
    void checkChange(Plant& plant) override;

	/**
	 * @brief Gets the name of this state
	 * @return String "Seedling"
	 */
    std::string name() override;

private:
	/**
	 * @brief Friend declaration to allow SingletonState access to constructor
	 */
    friend class SingletonState<SeedlingState>;

	/**
	 * @brief Private default constructor (singleton pattern)
	 */
    SeedlingState() = default;
};
#endif