/**
 * @file SpeciesFlyweight.cpp
 * @brief Implementation of the SpeciesFlyweight concrete flyweight class
 */

#include "SpeciesFlyweight.h"

/**
 * @brief Constructs a SpeciesFlyweight with all intrinsic state
 *
 * Initializes all member variables with the provided values representing
 * the shared characteristics of a plant species.
 */
SpeciesFlyweight::SpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice, double waterSensitivity,
								   double insecticideTolerance, double growthRate, Season thrivingSeason)
: sku(sku), name(name), biome(biome), basePrice(basePrice), waterSensitivity(waterSensitivity),
  insecticideTolerance(insecticideTolerance), growthRate(growthRate), thrivingSeason(thrivingSeason) {}

/**
 * @brief Returns the SKU identifier
 *
 * Provides access to the unique stock keeping unit identifier for this species.
 */
std::string SpeciesFlyweight::getSku()
{
	return sku;
}

/**
 * @brief Returns the species name
 *
 * Provides access to the name of this plant species.
 */
std::string SpeciesFlyweight::getName()
{
	return name;
}

/**
 * @brief Returns the natural biome
 *
 * Provides access to the biome where this species naturally occurs.
 */
std::string SpeciesFlyweight::getBiome()
{
	return biome;
}

/**
 * @brief Returns the base price
 *
 * Provides access to the base cost of this species.
 */
int SpeciesFlyweight::getCost()
{
	return basePrice;
}

/**
 * @brief Returns the water sensitivity
 *
 * Provides access to how sensitive this species is to water conditions.
 */
double SpeciesFlyweight::getWaterSensitivity()
{
	return waterSensitivity;
}

/**
 * @brief Returns the insecticide tolerance
 *
 * Provides access to this species' tolerance level to insecticides.
 */
double SpeciesFlyweight::getInsecticideTolerance()
{
	return insecticideTolerance;
}

/**
 * @brief Returns the growth rate
 *
 * Provides access to the rate at which this species grows.
 */
double SpeciesFlyweight::getGrowthRate()
{
	return growthRate;
}

/**
 * @brief Returns the thriving season
 *
 * Provides access to the season in which this species thrives best.
 */
Season SpeciesFlyweight::getThrivingSeason()
 {
	return thrivingSeason;
}