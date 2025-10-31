/**
 * @file UnsharedSpeciesFlyweight.cpp
 * @brief Implementation of the UnsharedSpeciesFlyweight unshared flyweight class
 */

#include "UnsharedSpeciesFlyweight.h"

/**
 * @brief Constructs an UnsharedSpeciesFlyweight with basic properties
 *
 * Initializes only the core member variables (sku, name, biome, basePrice).
 * Other properties (waterSensitivity, insecticideTolerance, growthRate,
 * thrivingSeason) remain uninitialized and may contain default or garbage values.
 */
UnsharedSpeciesFlyweight::UnsharedSpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice)
: sku(sku), name(name), biome(biome), basePrice(basePrice) {}

/**
 * @brief Returns the SKU identifier
 *
 * Provides access to the unique stock keeping unit identifier for this species.
 */
std::string UnsharedSpeciesFlyweight::getSku()
{
	return sku;
}

/**
 * @brief Returns the species name
 *
 * Provides access to the name of this plant species.
 */
std::string UnsharedSpeciesFlyweight::getName()
{
	return name;
}

/**
 * @brief Returns the natural biome
 *
 * Provides access to the biome where this species naturally occurs.
 */
std::string UnsharedSpeciesFlyweight::getBiome()
{
	return biome;
}

/**
 * @brief Returns the base price
 *
 * Provides access to the base cost of this species.
 */
int UnsharedSpeciesFlyweight::getCost()
{
	return basePrice;
}

/**
 * @brief Returns the water sensitivity
 *
 * Provides access to the water sensitivity value. Note that this value
 * is not initialized in the constructor and may contain default/undefined values.
 */
double UnsharedSpeciesFlyweight::getWaterSensitivity()
{
	return waterSensitivity;
}

/**
 * @brief Returns the insecticide tolerance
 *
 * Provides access to the insecticide tolerance level. Note that this value
 * is not initialized in the constructor and may contain default/undefined values.
 */
double UnsharedSpeciesFlyweight::getInsecticideTolerance()
{
	return insecticideTolerance;
}

/**
 * @brief Returns the growth rate
 *
 * Provides access to the growth rate value. Note that this value
 * is not initialized in the constructor and may contain default/undefined values.
 */
double UnsharedSpeciesFlyweight::getGrowthRate()
{
	return growthRate;
}

/**
 * @brief Returns the thriving season
 *
 * Provides access to the thriving season value. Note that this value
 * is not initialized in the constructor and may contain default/undefined values.
 */
Season UnsharedSpeciesFlyweight::getThrivingSeason()
{
	return thrivingSeason;
}