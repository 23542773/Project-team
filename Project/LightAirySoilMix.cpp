#include "LightAirySoilMix.h"

LightAirySoilMix::LightAirySoilMix() : SoilMix(90) {}

std::string LightAirySoilMix::name()
{ 
    return "Light Airy Soil Mix"; 
}
SoilMix* LightAirySoilMix::clone() const 
{ 
    return new LightAirySoilMix(*this); 
}