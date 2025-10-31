#include "DesertFactory.h"
DesertStrategy DesertFactory::s;

Pot* DesertFactory::createPot() 
{
	return new TerracottaPot();
}

SoilMix* DesertFactory::createSoilMix() 
{
	return new SandySoilMix();
}

CareStrategy* DesertFactory::careStrategy()
{
	return &s;
}