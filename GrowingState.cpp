#include "GrowingState.h"
#include "MatureState.h"

GrowingState& GrowingState::getInstance()
{
    static GrowingState s;
    return s;
}

GrowingState::GrowingState() {}

void GrowingState::onTick(Plant& plant) 
{
    plant.addHealth(1);
    plant.addWater(-10);
}

void GrowingState::checkChange(Plant& plant) 
{
    if (plant.getAgeDays() > 12 && plant.getHealth() > 70) 
	{
        plant.setState(&MatureState::getInstance());
    }
}

std::string GrowingState::name() const
{
    return "Growing";
}