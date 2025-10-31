/**
 * @file CareStrategy.h
 * @brief Defines the abstract CareStrategy interface for the Strategy pattern
 * @date 2025-10-28
 * @author Project Teams
 */

#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H
#include "Plant.h"

class Plant;

/**
 * @class CareStrategy
 * @brief Abstract base class representing different plant care strategies
 *
 * This class implements the Strategy pattern, allowing different care algorithms
 * to be applied to plants based on their biome or environmental requirements.
 * Each concrete strategy (Desert, Tropical, Mediterranean, Wetland, Indoor)
 * implements this interface to define biome-specific watering and fertilizing behavior.
 *
 * The Strategy pattern enables runtime selection of care approaches, making it easy
 * to adapt plant care to different environmental conditions without modifying the Plant class.
 */

class CareStrategy 
{

public:

    /**
	 * @brief Virtual destructor for proper cleanup of derived classes
	 */

	virtual ~CareStrategy() = default;

    /**
	 * @brief Applies strategy-specific watering behavior to a plant
	 * @param plant Reference to the plant to be watered
	 */

    virtual void water(Plant& plant) = 0;

    /**
     * @brief Applies strategy-specific fertilizing behavior to a plant
     * @param plant Reference to the plant to be fertilized
     */
    virtual void fertilize(Plant& plant) = 0;

    /**
     * @brief Applies strategy-specific insecticide spraying behavior to a plant
     * @param plant Reference to the plant to be sprayed
     */
    virtual void sprayInsecticide(Plant& plant) = 0;
};

#endif
