/**
 * @file PlantFlyweight.h
 * @brief Defines the Flyweight interface for plant species in the Flyweight pattern
 */

#ifndef PLANT_FLYWEIGHT_H
#define PLANT_FLYWEIGHT_H
#include <string>

/**
 * @enum Season
 * @brief Represents the four seasons in which plants can thrive
 */
enum class Season { Spring, Summer, Autumn, Winter };

/**
 * @class PlantFlyweight
 * @brief Abstract base class representing the Flyweight interface in the Flyweight design pattern
 *
 * This class defines the interface that all concrete flyweights must implement.
 * It contains methods to access intrinsic state (shared data) that is common across
 * multiple plant instances of the same species.
 */
class PlantFlyweight
{

public:

    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~PlantFlyweight() {};

    /**
     * @brief Gets the SKU (Stock Keeping Unit) identifier for the plant species
     * @return String containing the unique SKU identifier
     */
    virtual std::string getSku() = 0;

    /**
     * @brief Gets the name of the plant species
     * @return String containing the species name
     */
    virtual std::string getName()  = 0;

    /**
     * @brief Gets the biome where the plant species naturally occurs
     * @return String containing the biome information
     */
    virtual std::string getBiome() = 0;

    /**
     * @brief Gets the base cost/price of the plant species
     * @return Integer representing the cost in appropriate currency units
     */
    virtual int getCost()  = 0;

    /**
     * @brief Gets the water sensitivity of the plant species
     * @return Double value representing how sensitive the plant is to water conditions
     */
    virtual double getWaterSensitivity()  = 0;

    /**
     * @brief Gets the insecticide tolerance level of the plant species
     * @return Double value representing the plant's tolerance to insecticides
     */
    virtual double getInsecticideTolerance()  = 0;

    /**
     * @brief Gets the growth rate of the plant species
     * @return Double value representing the rate at which the plant grows
     */
    virtual double getGrowthRate()  = 0;

    /**
     * @brief Gets the season in which the plant species thrives best
     * @return Season enum value indicating the optimal growing season
     */
    virtual Season getThrivingSeason() = 0;
};

#endif