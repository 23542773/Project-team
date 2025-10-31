#include "GrowingState.h"
#include "MatureState.h"
#include "WiltingState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

GrowingState& GrowingState::getInstance()
{
    static GrowingState s;
    return s;
}

GrowingState::GrowingState() {}

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

std::string GrowingState::name() 
{
    return "Growing";
}