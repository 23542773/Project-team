#ifndef UNSHAREDSPECIESFLYWEIGHT_H
#define UNSHAREDSPECIESFLYWEIGHT_H
#include "PlantFlyweight.h"

/**
 * @class UnsharedSpeciesFlyweight
 * @brief Unshared flyweight for unique plant instances
 */
class UnsharedSpeciesFlyweight : public PlantFlyweight 
{
public:

    UnsharedSpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice);
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