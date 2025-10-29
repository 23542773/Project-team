/**
 * @file IndoorStrategy.h
 * @brief Defines the IndoorStrategy concrete strategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#ifndef INDOORSTRATEGY_H
#define INDOORSTRATEGY_H

#include "CareStrategy.h"

/**
 * @class IndoorStrategy
 * @brief Implements care strategy for indoor/houseplants
 *
 * This strategy is designed for plants grown in controlled indoor environments
 * with limited natural light and air circulation. Indoor plants require moderate,
 * consistent watering and regular but light fertilization to adapt to the
 * relatively stable indoor conditions.
 *
 * Typical plants using this strategy include pothos, snake plants, peace lilies,
 * and other common houseplants that thrive in indoor settings.
 */
class IndoorStrategy : public CareStrategy
{
public:
	/**
	 * @brief Applies moderate watering suitable for indoor plants
	 * @param plant Reference to the indoor plant to be watered
	 */
    void water(Plant& plant) override;

    /**
     * @brief Applies light fertilization suitable for indoor plants
     * @param plant Reference to the indoor plant to be fertilized
     */
    void fertilize(Plant& plant) override;
};

#endif