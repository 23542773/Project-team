#include "SpeciesFlyweight.h"

SpeciesFlyweight::SpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice, double waterSensitivity,
								   double insecticideTolerance, double growthRate, Season thrivingSeason)
: sku(sku), name(name), biome(biome), basePrice(basePrice), waterSensitivity(waterSensitivity),
  insecticideTolerance(insecticideTolerance), growthRate(growthRate), thrivingSeason(thrivingSeason) {}

std::string SpeciesFlyweight::getSku()  
{ 
	return sku; 
}

std::string SpeciesFlyweight::getName()  
{
	return name; 
}

std::string SpeciesFlyweight::getBiome() 
{ 
	return biome; 
}

int SpeciesFlyweight::getCost()  
{ 
	return basePrice; 
}

double SpeciesFlyweight::getWaterSensitivity()  
{ 
	return waterSensitivity; 
}

double SpeciesFlyweight::getInsecticideTolerance()  
{ 
	return insecticideTolerance; 
}

double SpeciesFlyweight::getGrowthRate()  
{ 
	return growthRate; 
}

Season SpeciesFlyweight::getThrivingSeason() 
 { 
	return thrivingSeason; 
}