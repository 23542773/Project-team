/**
 * @file IndoorStrategy.cpp
 * @brief Implementation of the IndoorStrategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#include "IndoorStrategy.h"
#include "Plant.h"

/**
 * @brief Applies moderate watering suitable for indoor plants
 *
 * Indoor plants are in controlled environments with limited evaporation
 * and require consistent, moderate watering. Adds water (+20) if moisture
 * falls below 60, maintaining steady moisture levels typical of indoor conditions.
 *
 * @param plant Reference to the indoor plant to be watered
 */
void IndoorStrategy::water(Plant& plant)
{
    if (plant.getMoisture() < 60) plant.addWater(20);
}

/**
 * @brief Applies light fertilization suitable for indoor plants
 *
 * Indoor plants have slower growth rates in controlled environments and
 * require lighter fertilization than outdoor plants. Adds health (+7) if
 * health is below 85, providing gentle nutrition.
 *
 * @param plant Reference to the indoor plant to be fertilized
 */
void IndoorStrategy::fertilize(Plant& plant)
{
    if (plant.getHealth() < 85) plant.addHealth(7);
}