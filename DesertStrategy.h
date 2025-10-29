/**
 * @file DesertStrategy.h
 * @brief Defines the DesertStrategy concrete strategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#ifndef DESERTSTRATEGY_H
#define DESERTSTRATEGY_H

#include "CareStrategy.h"

/**
 * @class DesertStrategy
 * @brief Implements care strategy for desert/arid climate plants
 *
 * This strategy is designed for plants that thrive in dry, arid conditions.
 * Desert plants require minimal watering and conservative fertilization to
 * avoid overwatering and nutrient buildup, which can harm them.
 *
 * Typical plants using this strategy include cacti, succulents, and other
 * drought-resistant species.
 */
class DesertStrategy : public CareStrategy
{
public:
	/**
	 * @brief Applies minimal watering suitable for desert plants
	 * @param plant Reference to the desert plant to be watered
	 */
	void water(Plant& plant) override;

	/**
	 * @brief Applies conservative fertilization suitable for desert plants
	 * @param plant Reference to the desert plant to be fertilized
	 */
    void fertilize(Plant& plant) override;
};

#endif