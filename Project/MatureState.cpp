/**
 * @file MatureState.cpp
 * @brief Implementation of the MatureState class
 */
#include "MatureState.h"
#include "WiltingState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

/**
 * @brief Implements state transition logic for mature plants
 *
 * Resource consumption: -5 water, -5 insecticide per check (high demand)
 *
 * Health adjustments:
 * - Gains +4 health if moisture >= 55 and insecticide >= 55
 * - Loses -5 health if moisture < 30
 * - Loses -4 health if insecticide < 30
 *
 * State transitions:
 * - To DeadState: if health <= 0
 * - To WiltingState: if health <= 50
 * @param plant Reference to the Plant object whose state is being checked
 */
void MatureState::checkChange(Plant& plant)
{
    plant.addWater(-5);
    plant.addInsecticide(-5);

    if (plant.getMoisture() >= 55 && plant.getInsecticide() >= 55)
    {
        plant.addHealth(4);
    }
    else if (plant.getMoisture() < 50 || plant.getInsecticide() < 50)
    {
        if (plant.getMoisture() < 30) plant.addHealth(-5);
        if (plant.getInsecticide() < 30) plant.addHealth(-4);
    }

    if (plant.getHealth() <= 0)
    {
        plant.setState(&DeadState::getInstance());
    }
    else if (plant.getHealth() <= 50)
    {
        plant.setState(&WiltingState::getInstance());
    }
}

/**
 * @brief Indicates that this state is the mature state
 * @return True
 */
bool MatureState::isMature()
{
    return true;
}

/**
 * @brief Returns the name identifier for this state
 * @return The string "Matured"
 */
std::string MatureState::name()
{
    return "Matured";
}