/**
 * @file MediterraneanStrategy.h
 * @brief Defines the MediterraneanStrategy concrete strategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#ifndef MEDITERRANEANSTRATEGY_H
#define MEDITERRANEANSTRATEGY_H

#include "CareStrategy.h"

/**
 * @class MediterraneanStrategy
 * @brief Implements care strategy for Mediterranean climate plants
 *
 * This strategy is designed for plants that thrive in Mediterranean climates
 * characterized by hot, dry summers and mild, wet winters. These plants require
 * moderate watering and balanced fertilization, adapting to seasonal variations.
 *
 * Typical plants using this strategy include lavender, rosemary, olive trees,
 * and other herbs and shrubs native to Mediterranean regions.
 */
class MediterraneanStrategy : public CareStrategy
{
public:
	/**
	 * @brief Applies moderate watering suitable for Mediterranean plants
	 * @param plant Reference to the Mediterranean plant to be watered
	 */
    void water(Plant& plant) override;

    /**
     * @brief Applies balanced fertilization suitable for Mediterranean plants
     * @param plant Reference to the Mediterranean plant to be fertilized
     */
    void fertilize(Plant& plant) override;
};

#endif