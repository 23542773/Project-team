#include "SpeciesFlyweight.h"

SpeciesFlyweight::SpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice)
: sku(sku), name(name), biome(biome), basePrice(basePrice) {}

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