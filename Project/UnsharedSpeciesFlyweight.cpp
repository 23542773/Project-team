#include "UnsharedSpeciesFlyweight.h"

UnsharedSpeciesFlyweight::UnsharedSpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice)
: sku(sku), name(name), biome(biome), basePrice(basePrice) {}

std::string UnsharedSpeciesFlyweight::getSku()  
{ 
	return sku; 
}

std::string UnsharedSpeciesFlyweight::getName()  
{ 
	return name; 
}

std::string UnsharedSpeciesFlyweight::getBiome()  
{ 
	return biome; 
}

int UnsharedSpeciesFlyweight::getCost()  
{ 
	return basePrice; 
}

double UnsharedSpeciesFlyweight::getWaterSensitivity()  
{ 
	return waterSensitivity; 
}

double UnsharedSpeciesFlyweight::getInsecticideTolerance()  
{ 
	return insecticideTolerance; 
}

double UnsharedSpeciesFlyweight::getGrowthRate()  
{ 
	return growthRate; 
}

Season UnsharedSpeciesFlyweight::getThrivingSeason()  
{ 
	return thrivingSeason; 
}