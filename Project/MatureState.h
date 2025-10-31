/**
 * @file MatureState.h
 * @brief Defines the MatureState concrete state class
 */
#ifndef MATURESTATE_H
#define MATURESTATE_H
#include "PlantState.h"
#include "SingletonState.h"

/**
 * @class MatureState
 * @brief Concrete State class representing a fully grown plant
 *
 * This state handles the logic for a mature plant with higher resource demands.
 * It can transition to WiltingState or DeadState if care is inadequate.
 */
class MatureState : public SingletonState<MatureState>
{
public:

    /**
     * @brief Evaluates plant conditions and manages state transitions
     * @param plant Reference to the Plant object being evaluated
     *
     * Decrements water and insecticide levels, adjusts health based on care conditions,
     * and transitions to DeadState or WiltingState.
     */
    void checkChange(Plant& plant) override;

    /**
     * @brief Gets the name of this state
     * @return String "Matured"
     */
    std::string name() override;

    /**
     * @brief Checks if the plant is in a mature state
     * @return True, as this is the mature state
     */
    bool isMature() override;

private:

    /**
     * @brief Friend declaration to allow SingletonState access to constructor
     */
    friend class SingletonState<MatureState>;

    /**
     * @brief Private default constructor (singleton pattern)
     */
    MatureState() = default;
};

#endif