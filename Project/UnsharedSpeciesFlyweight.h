/**
 * @file UnsharedSpeciesFlyweight.h
 * @brief Defines the unshared Flyweight for plant species
 */

#ifndef UNSHAREDSPECIESFLYWEIGHT_H
#define UNSHAREDSPECIESFLYWEIGHT_H
#include "PlantFlyweight.h"

/**
 * @class UnsharedSpeciesFlyweight
 * @brief Unshared Flyweight class representing plant species with unique extrinsic state
 *
 * This class represents an unshared flyweight in the Flyweight pattern. Unlike
 * SpeciesFlyweight which shares intrinsic state, this class may contain unique
 * extrinsic state that cannot be shared. Some member variables may be uninitialized
 * or set dynamically, representing state that varies between instances.
 */
class UnsharedSpeciesFlyweight : public PlantFlyweight
{
public:

	/**
	 * @brief Constructs an UnsharedSpeciesFlyweight with basic properties
	 * @param sku Unique stock keeping unit identifier for the species
	 * @param name The species name
	 * @param biome The natural biome of the species
	 * @param basePrice The base cost/price of the species
	 *
	 * Note: This constructor only initializes core properties. Other properties
	 * (waterSensitivity, insecticideTolerance, growthRate, thrivingSeason) are
	 * not initialized and may contain default values.
	 */
    UnsharedSpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice);

	/**
	 * @brief Gets the SKU identifier
	 * @return String containing the unique SKU
	 */
    std::string getSku() override;

	/**
	 * @brief Gets the species name
	 * @return String containing the species name
	 */
    std::string getName() override;

	/**
	 * @brief Gets the natural biome
	 * @return String containing the biome information
	 */
    std::string getBiome() override;

	/**
	 * @brief Gets the base price
	 * @return Integer representing the base cost
	 */
    int getCost() override;

	/**
	 * @brief Gets the water sensitivity value
	 * @return Double representing water sensitivity (may be uninitialized)
	 */
    double getWaterSensitivity() override;

	/**
	 * @brief Gets the insecticide tolerance level
	 * @return Double representing insecticide tolerance (may be uninitialized)
	 */
    double getInsecticideTolerance() override;

	/**
	 * @brief Gets the growth rate
	 * @return Double representing the growth rate (may be uninitialized)
	 */
    double getGrowthRate() override;

	/**
	 * @brief Gets the thriving season
	 * @return Season enum value (may be uninitialized)
	 */
    Season getThrivingSeason() override;

private:

	/**
	 * @brief Unique stock keeping unit identifier
	 */
    std::string sku;

	/**
	 * @brief Species name
	 */
	std::string name;

	/**
	 * @brief Natural biome of the species
	 */
	std::string biome;

	/**
	 * @brief Base price/cost of the species
	 */
    int basePrice;

	/**
	 * @brief Water sensitivity value (not initialized in constructor)
	 */
    double waterSensitivity;

	/**
	 * @brief Insecticide tolerance level (not initialized in constructor)
	 */
    double insecticideTolerance;

	/**
	 * @brief Growth rate of the species (not initialized in constructor)
	 */
    double growthRate;

	/**
	 * @brief Season in which the species thrives (not initialized in constructor)
	 */
    Season thrivingSeason;
};

#endif