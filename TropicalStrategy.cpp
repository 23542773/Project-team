/**
 * @file TropicalStrategy.cpp
 * @brief Implementation of the TropicalStrategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#include "TropicalStrategy.h"
#include "Plant.h"

/**
 * @brief Applies frequent watering suitable for tropical plants
 *
 * Tropical plants thrive in humid, moist environments and require
 * frequent watering. Adds generous water (+25) if moisture falls below 70,
 * maintaining the high moisture levels tropical plants need.
 *
 * @param plant Reference to the tropical plant to be watered
 */
void TropicalStrategy::water(Plant& plant)
{
    if (plant.getMoisture() < 70) plant.addWater(25);
}

/**
 * @brief Applies regular fertilization suitable for tropical plants
 *
 * Tropical plants grow vigorously in nutrient-rich environments and
 * benefit from regular fertilization. Adds significant health (+10) if
 * health is below 90, supporting rapid growth.
 *
 * @param plant Reference to the tropical plant to be fertilized
 */
void TropicalStrategy::fertilize(Plant& plant)
{
    if (plant.getHealth() < 90) plant.addHealth(10);
}