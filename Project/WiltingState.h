/**
 * @file WiltingState.h
 * @brief Defines the WiltingState concrete state class
 */
#ifndef WILTINGSTATE_H
#define WILTINGSTATE_H
#include "PlantState.h"
#include "SingletonState.h"

/**
 * @class WiltingState
 * @brief Concrete State class representing a stressed plant in decline
 *
 * This state typically results from inadequate moisture or insecticide levels,
 * causing a drop in health. The plant requires significantly improved conditions
 * to recover, otherwise it will transition to the DeadState.
 */
class WiltingState : public SingletonState<WiltingState>
{
public:

    /**
     * @brief Evaluates plant conditions and manages state transitions
     * @param plant Reference to the Plant object being evaluated
     *
     * Decrements water and insecticide levels (high consumption), adjusts health based on
     * care conditions, and transitions back to MatureState (if recovered) or to DeadState.
     */
    void checkChange(Plant& plant) override;

    /**
     * @brief Gets the name of this state
     * @return String "Wilting"
     */
    std::string name() override;

private:

    /**
     * @brief Friend declaration to allow SingletonState access to constructor
     */
    friend class SingletonState<WiltingState>;

    /**
     * @brief Private default constructor (singleton pattern)
     */
    WiltingState() = default;
};

#endif