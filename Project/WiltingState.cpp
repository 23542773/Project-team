#include "WiltingState.h"
#include "MatureState.h"
#include "DeadState.h"
#include "Plant.h"
#include "SpeciesFlyweight.h"
#include <iostream>

WiltingState& WiltingState::getInstance() 
{
    static WiltingState s;
    return s;
}

WiltingState::WiltingState() {}

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

std::string WiltingState::name() 
{
    return "Wilting";
}