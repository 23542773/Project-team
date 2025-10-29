#include "SeedlingState.h"
#include "GrowingState.h"

SeedlingState& SeedlingState::getInstance() 
{
    static SeedlingState instance;  
    return instance;
}

SeedlingState::SeedlingState() {}

void SeedlingState::onTick(Plant& p) 
{
	p.addHealth(2);
}

void SeedlingState::checkChange(Plant& plant)
{
	if (plant.getAgeDays() > 5) 
	{
        plant.setState(&GrowingState::getInstance());
    }
}

std::string SeedlingState::name() const
{ 
	return "Seedling";
}
