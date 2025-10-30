/**
 * @file WetlandStrategy.cpp
 * @brief Implementation of the WetlandStrategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#include "WetlandStrategy.h"
#include "Plant.h"

/**
 * @brief Applies heavy watering suitable for wetland plants
 *
 * Wetland plants are adapted to saturated soil conditions and require
 * very frequent, heavy watering. Adds substantial water (+30) if moisture
 * falls below 80, maintaining the consistently wet environment these plants need.
 *
 * @param plant Reference to the wetland plant to be watered
 */
void WetlandStrategy::water(Plant& plant)
{
    if (plant.getMoisture() < 80) plant.addWater(30);
}

/**
 * @brief Applies moderate fertilization suitable for wetland plants
 *
 * Wetland plants grow in nutrient-rich aquatic environments and benefit
 * from generous fertilization. Adds significant health (+12) if health
 * is below 90, supporting vigorous growth in waterlogged conditions.
 *
 * @param plant Reference to the wetland plant to be fertilized
 */
void WetlandStrategy::fertilize(Plant& plant)
{
    if (plant.getHealth() < 90) plant.addHealth(12);
}