#include "SeedlingState.h"
#include "GrowingState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

SeedlingState& SeedlingState::getInstance() 
{
    static SeedlingState instance;  
    return instance;
}

SeedlingState::SeedlingState() {}

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

std::string SeedlingState::name()
{ 
	return "Seedling";
}
