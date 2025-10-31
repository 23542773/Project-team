#include "PeatSoilMix.h"

PeatSoilMix::PeatSoilMix() : SoilMix(50) {}

std::string PeatSoilMix::name()   
{ 
    return "Peat Soil Mix"; 
}

SoilMix* PeatSoilMix::clone() const  
{
     return new PeatSoilMix(*this); 
}