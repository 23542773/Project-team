/**
 * @file TropicalStrategy.h
 * @brief Defines the TropicalStrategy concrete strategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#ifndef TROPICALSTRATEGY_H
#define TROPICALSTRATEGY_H

#include "CareStrategy.h"

/**
 * @class TropicalStrategy
 * @brief Implements care strategy for tropical climate plants
 *
 * This strategy is designed for plants that thrive in warm, humid tropical
 * environments. Tropical plants require frequent watering and regular
 * fertilization to support their vigorous growth in high-nutrient, moist conditions.
 *
 * Typical plants using this strategy include ferns, orchids, bromeliads,
 * and other moisture-loving tropical species.
 */

class TropicalStrategy : public CareStrategy 
{
public:

    /**
	 * @brief Applies frequent watering suitable for tropical plants
	 * @param plant Reference to the tropical plant to be watered
	 */
    void water(Plant& plant) override;

    /**
     * @brief Applies regular fertilization suitable for tropical plants
     * @param plant Reference to the tropical plant to be fertilized
     */
    void fertilize(Plant& plant) override;

    /**
     * @brief Applies insecticide spraying suitable for tropical plants
     * @param plant Reference to the tropical plant to be sprayed
     */
    void sprayInsecticide(Plant& plant) override;
};

#endif 