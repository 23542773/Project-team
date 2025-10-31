#include "AquaticSoilMix.h"

AquaticSoilMix::AquaticSoilMix() : SoilMix(80) {}

std::string AquaticSoilMix::name()  
{ 
    return "Aquatic Soil Mix"; 
}
SoilMix* AquaticSoilMix::clone() const
{ 
    return new AquaticSoilMix(*this); 
}