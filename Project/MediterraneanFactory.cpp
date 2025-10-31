#include "MediterraneanFactory.h"
MediterraneanStrategy MediterraneanFactory::s;

Pot* MediterraneanFactory::createPot() 
{
	return new UnglazedClayPot();
}

SoilMix* MediterraneanFactory::createSoilMix() 
{
	return new GrittyLimeSoilMix();
}

CareStrategy* MediterraneanFactory::careStrategy()
{
	return &s;
}