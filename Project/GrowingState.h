/**
 * @file GrowingState.h
 * @brief Defines the GrowingState concrete state class
 */
#ifndef GROWINGSTATE_H
#define GROWINGSTATE_H
#include "PlantState.h"
#include "SingletonState.h"

/**
 * @class GrowingState
 * @brief Concrete State class representing a plant in its primary growth stage
 *
 * This state handles the logic for a healthy plant actively growing. It manages resource
 * consumption and health adjustments, and transitions to MatureState, WiltingState,
 * or DeadState based on conditions.
 */
class GrowingState : public SingletonState<GrowingState>
{
public:
    /**
     * @brief Evaluates plant conditions and manages state transitions
     * @param plant Reference to the Plant object being evaluated
     *
     * Decrements water and insecticide levels, adjusts health based on care conditions,
     * and transitions to DeadState, WiltingState, or MatureState based on age, health,
     * and species characteristics.
     */
    void checkChange(Plant& plant) override;

    /**
     * @brief Gets the name of this state
     * @return String "Growing"
     */
    std::string name() override;

private:
    /**
     * @brief Friend declaration to allow SingletonState access to constructor
     */
    friend class SingletonState<GrowingState>;

    /**
     * @brief Private default constructor (singleton pattern)
     */
    GrowingState() = default;
};
#endif