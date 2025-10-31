#include "WetlandFactory.h"
WetlandStrategy WetlandFactory::s;

Pot* WetlandFactory::createPot() 
{
	return new AquaticBasketPot();
}

SoilMix* WetlandFactory::createSoilMix() 
{
	return new AquaticSoilMix();
}

CareStrategy* WetlandFactory::careStrategy()
{
	return &s;
}