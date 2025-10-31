/**
 * @file WetlandStrategy.h
 * @brief Defines the WetlandStrategy concrete strategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#ifndef WETLANDSTRATEGY_H
#define WETLANDSTRATEGY_H

#include "CareStrategy.h"

/**
 * @class WetlandStrategy
 * @brief Implements care strategy for wetland/bog plants
 *
 * This strategy is designed for plants that thrive in wetland environments
 * with consistently high moisture levels. Wetland plants require very frequent
 * watering to maintain saturated soil conditions and moderate fertilization
 * to support growth in nutrient-rich aquatic environments.
 *
 * Typical plants using this strategy include water lilies, cattails, sedges,
 * and other aquatic or semi-aquatic species.
 */

class WetlandStrategy : public CareStrategy 
{
public:


    /**
	 * @brief Applies heavy watering suitable for wetland plants
	 * @param plant Reference to the wetland plant to be watered
	 */
    void water(Plant& plant) override;

    /**
     * @brief Applies moderate fertilization suitable for wetland plants
     * @param plant Reference to the wetland plant to be fertilized
     */
    void fertilize(Plant& plant) override;

    /**
     * @brief Applies insecticide spraying suitable for wetland plants
     * @param plant Reference to the wetland plant to be sprayed
     */
    void sprayInsecticide(Plant& plant) override;
};

#endif