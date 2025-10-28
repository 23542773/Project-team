#include "IndoorFactory.h"
IndoorStrategy IndoorFactory::s;

Pot* IndoorFactory::createPot() 
{
	return new CeramicPot();
}

SoilMix* IndoorFactory::createSoilMix() 
{
	return new LightAirySoilMix();
}

CareStrategy* IndoorFactory::careStrategy()
{
	return &s;
}