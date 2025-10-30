#include "MatureState.h"
#include "WiltingState.h"

MatureState& MatureState::getInstance()
{
    static MatureState s;
    return s;
}

MatureState::MatureState() {}

void MatureState::onTick(Plant& plant) 
{
    plant.addWater(-15);
    if (plant.getMoisture() < 30) plant.addHealth(-3);
}

void MatureState::checkChange(Plant& plant) 
{
    if (plant.getHealth() < 40 || plant.getMoisture() < 20) 
	{
		plant.setState(&WiltingState::getInstance());
	}
	
}

std::string MatureState::name() 
{
    return "Matured";
}