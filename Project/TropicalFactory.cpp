#include "TropicalFactory.h"
TropicalStrategy TropicalFactory::s;

Pot* TropicalFactory::createPot() 
{
	return new GlazedCeramicPot();
}

SoilMix* TropicalFactory::createSoilMix() 
{
	return new PeatSoilMix();
}

CareStrategy* TropicalFactory::careStrategy()
{
	return &s;
}