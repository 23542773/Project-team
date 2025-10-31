#include "UnglazedClayPot.h"

UnglazedClayPot::UnglazedClayPot() : Pot(70) {}

std::string UnglazedClayPot::name()  
{ 
    return "Unglazed Clay Pot"; 
}

Pot* UnglazedClayPot::clone() const 
{
    return new UnglazedClayPot(*this); 
}