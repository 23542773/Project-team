/**
 * @file SeedlingState.cpp
 * @brief Implementation of the SeedlingState class
 */

#include "SeedlingState.h"
#include "GrowingState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

/**
 * @brief Implements state transition logic for seedling plants
 *
 * Resource consumption: -1 water, -1 insecticide per check
 *
 * Health adjustments:
 * - Gains +2 health if moisture >= 40 and insecticide >= 40
 * - Loses -3 health if moisture < 30
 * - Loses -2 health if insecticide < 30
 *
 * State transitions:
 * - To DeadState: if health <= 0
 * - To GrowingState: if age > adjusted threshold and health > 40
 * (threshold = 5.0 * growth rate * season factor)
 * (season factor = 0.8 in thriving season, 1.2 otherwise)
 * @param plant Reference to the Plant object whose state is being checked
 */
void SeedlingState::checkChange(Plant& plant)
{
    plant.addWater(-1);
    plant.addInsecticide(-1);

    if (plant.getMoisture() >= 40 && plant.getInsecticide() >= 40)
    {
        plant.addHealth(2);
    }
    else if (plant.getMoisture() < 30 || plant.getInsecticide() < 30)
    {
        if (plant.getMoisture() < 30) plant.addHealth(-3);
        if (plant.getInsecticide() < 30) plant.addHealth(-2);
    }

    auto* sp = plant.getSpeciesFly();
    double growthRate = sp->getGrowthRate();
    Season current = plant.currentSeason();
    Season thrive = sp->getThrivingSeason();

    double seasonFactor = (current == thrive) ? 0.8 : 1.2;
    double adjustedThreshold = 5.0 * growthRate * seasonFactor;

    if (plant.getHealth() <= 0)
    {
        plant.setState(&DeadState::getInstance());
    }

    else if (plant.getAgeDays() > adjustedThreshold && plant.getHealth() > 40)
    {
        plant.setState(&GrowingState::getInstance());
    }
}

/**
 * @brief Returns the name identifier for this state
 * @return The string "Seedling"
 */
std::string SeedlingState::name()
{
	return "Seedling";
}