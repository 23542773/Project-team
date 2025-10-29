#ifndef SPECIESFLYWEIGHT_H
#define SPECIESFLYWEIGHT_H
#include "PlantFlyweight.h"

/**
 * @class SpeciesFlyweight
 * @brief Concrete flyweight for shared plant species data
 */
class SpeciesFlyweight : public PlantFlyweight 
{

public:

	SpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice);
	std::string getSku() override;
    std::string getName() override;
    std::string getBiome() override;
    int getCost() override;

private:

    std::string sku;
	std::string name; 
	std::string biome;
    int basePrice;
};

#endif