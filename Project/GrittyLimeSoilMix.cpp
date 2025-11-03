#include "GrittyLimeSoilMix.h"

GrittyLimeSoilMix::GrittyLimeSoilMix() : SoilMix(120) {}

std::string GrittyLimeSoilMix::name()  
{
     return "Gritty Lime Soil Mix"; 
    }
SoilMix* GrittyLimeSoilMix::clone() const

{ 
    return new GrittyLimeSoilMix(*this); 
}