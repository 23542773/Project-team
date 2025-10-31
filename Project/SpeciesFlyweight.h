/**
 * @file SpeciesFlyweight.h
 * @brief Defines the concrete shared Flyweight for plant species
 */

#ifndef SPECIESFLYWEIGHT_H
#define SPECIESFLYWEIGHT_H
#include "PlantFlyweight.h"


/**
 * @class SpeciesFlyweight
 * @brief Concrete Flyweight class representing shared intrinsic state of plant species
 *
 * This class implements the Flyweight pattern by storing intrinsic state (data that can be
 * shared across multiple plant instances). All data members represent characteristics that
 * are common to all plants of the same species, making them ideal for sharing to reduce
 * memory consumption.
 */
class SpeciesFlyweight : public PlantFlyweight
{

public:

	/**
	 * @brief Constructs a SpeciesFlyweight with all intrinsic state data
	 * @param sku Unique stock keeping unit identifier for the species
	 * @param name The species name
	 * @param biome The natural biome of the species
	 * @param basePrice The base cost/price of the species
	 * @param waterSensitivity The species' sensitivity to water conditions
	 * @param insecticideTolerance The species' tolerance to insecticides
	 * @param growthRate The rate at which the species grows
	 * @param thrivingSeason The season in which the species thrives best
	 */
	SpeciesFlyweight(std::string sku, std::string name, std::string biome, int basePrice, double waterSensitivity,
    double insecticideTolerance, double growthRate, Season thrivingSeason);

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
	 * @return Double representing water sensitivity
	 */
    double getWaterSensitivity();

	/**
	 * @brief Gets the insecticide tolerance level
	 * @return Double representing insecticide tolerance
	 */
    double getInsecticideTolerance();

	/**
	 * @brief Gets the growth rate
	 * @return Double representing the growth rate
	 */
    double getGrowthRate();

	/**
	 * @brief Gets the optimal thriving season
	 * @return Season enum value
	 */
    Season getThrivingSeason();

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
	 * @brief Water sensitivity value
	 */
    double waterSensitivity;

	/**
	 * @brief Insecticide tolerance level
	 */
    double insecticideTolerance;

	/**
	 * @brief Growth rate of the species
	 */
    double growthRate;

	/**
	 * @brief Season in which the species thrives
	 */
    Season thrivingSeason;
};

#endif