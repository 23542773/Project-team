#ifndef SPECIESFLYWEIGHT_H
#define SPECIESFLYWEIGHT_H
#include "PlantFlyweight.h"


class SpeciesFlyweight : public PlantFlyweight 
{

public:

	SpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice, double waterSensitivity,
    double insecticideTolerance, double growthRate, Season thrivingSeason);
	std::string getSku() override;
    std::string getName() override;
    std::string getBiome() override;
    int getCost() override;
    double getWaterSensitivity();
    double getInsecticideTolerance();
    double getGrowthRate();
    Season getThrivingSeason();

private:

    std::string sku;
	std::string name; 
	std::string biome;
    int basePrice;
    double waterSensitivity;
    double insecticideTolerance;
    double growthRate;
    Season thrivingSeason;
};

#endif