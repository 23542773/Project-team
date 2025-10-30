/**
 * @file MediterraneanStrategy.cpp
 * @brief Implementation of the MediterraneanStrategy class
 * @date 2025-10-28
 * @author Project Teams
 */

#include "MediterraneanStrategy.h"
#include "Plant.h"

/**
 * @brief Applies moderate watering suitable for Mediterranean plants
 *
 * Mediterranean plants are adapted to seasonal rainfall patterns with
 * dry summers. Adds moderate water (+20) if moisture falls below 50,
 * maintaining balanced moisture levels.
 *
 * @param plant Reference to the Mediterranean plant to be watered
 */
void MediterraneanStrategy::water(Plant& plant)
{
    if (plant.getMoisture() < 50) plant.addWater(20);
}

/**
 * @brief Applies balanced fertilization suitable for Mediterranean plants
 *
 * Mediterranean plants benefit from moderate fertilization to support
 * steady growth. Adds health (+8) if health is below 85, providing
 * balanced nutrition without excess.
 *
 * @param plant Reference to the Mediterranean plant to be fertilized
 */
void MediterraneanStrategy::fertilize(Plant& plant)
{
    if (plant.getHealth() < 85) plant.addHealth(8);
}