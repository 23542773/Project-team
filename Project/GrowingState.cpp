/**
 * @file GrowingState.cpp
 * @brief Implementation of the GrowingState class
 */
#include "GrowingState.h"
#include "MatureState.h"
#include "WiltingState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

/**
 * @brief Implements state transition logic for growing plants
 *
 * Resource consumption: -2 water, -1 insecticide per check
 *
 * Health adjustments:
 * - Gains +3 health if moisture >= 40 and insecticide >= 40
 * - Loses -4 health if moisture < 25
 * - Loses -3 health if insecticide < 25
 *
 * State transitions:
 * - To DeadState: if health <= 0
 * - To WiltingState: if health <= 20
 * - To MatureState: if age > adjusted threshold and health > 50
 * (threshold = 12.0 * growth rate * season factor)
 * (season factor = 0.8 in thriving season, 1.2 otherwise)
 * @param plant Reference to the Plant object whose state is being checked
 */
void GrowingState::checkChange(Plant& plant)
{
    plant.addWater(-2);
    plant.addInsecticide(-1);

    if (plant.getMoisture() >= 40 && plant.getInsecticide() >= 40)
    {
        plant.addHealth(3);
    }
    else if (plant.getMoisture() < 25 || plant.getInsecticide() < 25)
    {
        if (plant.getMoisture() < 25) plant.addHealth(-4);

        if (plant.getInsecticide() < 25) plant.addHealth(-3);
    }

    auto* sp = plant.getSpeciesFly();
    double growthRate = sp->getGrowthRate();
    double adjustedThreshold = 12.0 * growthRate * ((plant.currentSeason() == sp->getThrivingSeason()) ? 0.8 : 1.2);

    if (plant.getHealth() <= 0)
    {
        plant.setState(&DeadState::getInstance());
    }
    
    else if (plant.getHealth() <= 20)
    {
        plant.setState(&WiltingState::getInstance());
    }

    else if (plant.getAgeDays() > adjustedThreshold && plant.getHealth() > 50)
    {
        plant.setState(&MatureState::getInstance());
    }
}

/**
 * @brief Returns the name identifier for this state
 * @return The string "Growing"
 */
std::string GrowingState::name() 
{
    return "Growing";
}