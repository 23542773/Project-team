#include "DeadState.h"

DeadState& DeadState::getInstance()
{
    static DeadState s;
    return s;
}

DeadState::DeadState() {}

void DeadState::checkChange(Plant&) 
{

}

std::string DeadState::name() 
{
    return "Dead";
}