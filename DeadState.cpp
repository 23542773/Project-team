#include "DeadState.h"

DeadState& DeadState::getInstance()
{
    static DeadState s;
    return s;
}

DeadState::DeadState() {}

void DeadState::onTick(Plant&) 
{
	//Doesn't do anything since the plant is dead
}

void DeadState::checkChange(Plant&) 
{
    //Doesn't do anything since the plant is dead
}

std::string DeadState::name() const
{
    return "Dead";
}
