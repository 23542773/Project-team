#include "SandySoilMix.h"

SandySoilMix::SandySoilMix() : SoilMix(35) {}

std::string SandySoilMix::name() 
{ 
    return "Sandy Soil Mix"; 
}

SoilMix* SandySoilMix::clone() const  
{ 
    return new SandySoilMix(*this); 
}