/**
 * @file DesertStrategy.cpp
 * @brief Implementation of the DesertStrategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#include "DesertStrategy.h"
#include "Plant.h"

/**
 * @brief Applies minimal watering suitable for desert plants
 *
 * Desert plants are drought-tolerant and require infrequent watering.
 * Only adds water (+15) if moisture falls below 30, preventing overwatering
 * which can damage desert-adapted species.
 *
 * @param plant Reference to the desert plant to be watered
 */
void DesertStrategy::water(Plant& plant)
{
    if (plant.getMoisture() < 30) plant.addWater(15);
}

/**
 * @brief Applies conservative fertilization suitable for desert plants
 *
 * Desert plants have adapted to low-nutrient environments and require
 * minimal fertilization. Only adds health (+5) if health is below 80,
 * avoiding nutrient overload.
 *
 * @param plant Reference to the desert plant to be fertilized
 */
void DesertStrategy::fertilize(Plant& plant)
{
    if (plant.getHealth() < 80) plant.addHealth(5);
}