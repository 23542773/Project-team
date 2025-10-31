/**
 * @file WiltingState.cpp
 * @brief Implementation of the WiltingState class
 */
#include "WiltingState.h"
#include "MatureState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

/**
 * @brief Implements state transition logic for wilting plants
 *
 * Resource consumption: -3 water, -3 insecticide per check (high consumption)
 *
 * Health adjustments:
 * - Gains +5 health if moisture > 60 and insecticide > 60 (strong recovery)
 * - Loses -3 health for poor moisture (< 40)
 * - Loses -3 health for poor insecticide levels (< 40)
 *
 * State transitions:
 * - To MatureState: if health > 60 AND moisture > 40 AND insecticide > 40 (recovery)
 * - To DeadState: if health <= 0
 * @param plant Reference to the Plant object whose state is being checked
 */
void WiltingState::checkChange(Plant& plant)
{
    plant.addWater(-3);
    plant.addInsecticide(-3);

    if (plant.getMoisture() > 60 && plant.getInsecticide() > 60)
    {
        plant.addHealth(5);
    }
    else if (plant.getMoisture() < 40 || plant.getInsecticide() < 40)
    {
        if (plant.getMoisture() < 40) plant.addHealth(-3);
        if (plant.getInsecticide() < 40) plant.addHealth(-3);
    }

    if (plant.getHealth() > 60 && plant.getMoisture() > 40 && plant.getInsecticide() > 40)
    {
        plant.setState(&MatureState::getInstance());
    }
    
    else if (plant.getHealth() <= 0)
    {
        plant.setState(&DeadState::getInstance());
    }
}

/**
 * @brief Returns the name identifier for this state
 * @return The string "Wilting"
 */
std::string WiltingState::name() 
{
    return "Wilting";
}