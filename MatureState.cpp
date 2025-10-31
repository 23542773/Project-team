#include "MatureState.h"
#include "WiltingState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

MatureState& MatureState::getInstance()
{
    static MatureState s;
    return s;
}

MatureState::MatureState() {}

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

bool MatureState::isMature()
{
    return true;
}

std::string MatureState::name()
{
    return "Matured";
}