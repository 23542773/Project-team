#include "SoilMix.h"

SoilMix::SoilMix(int c) : cost(c) {}

int SoilMix::getCost() const
{ 
    return cost; 
}