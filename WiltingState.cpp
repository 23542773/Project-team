#include "WiltingState.h"
#include "MatureState.h"
#include "DeadState.h"

WiltingState& WiltingState::getInstance() 
{
    static WiltingState s;
    return s;
}

WiltingState::WiltingState() {}

void WiltingState::onTick(Plant& plant) 
{
    plant.addWater(-5);
    plant.addHealth(-4);
}

void WiltingState::checkChange(Plant& plant) 
{
    if (plant.getHealth() <= 0) 
	{
        plant.setState(&DeadState::getInstance()); 
    } 
	else if (plant.getHealth() > 60 && plant.getMoisture() > 40) 
	{
        plant.setState(&MatureState::getInstance()); 
    }
}

std::string WiltingState::name() 
{
    return "Wilting";
}