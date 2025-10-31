/**
 * @file TropicalStrategy.cpp
 * @brief Implements the TropicalStrategy class for tropical plant care.
 * 
 * This strategy defines plant care routines tailored to tropical species,
 * emphasizing frequent watering, nutrient-rich fertilization, and strong
 * pest management to reflect the warm, humid environments in which these
 * plants naturally thrive.
 * 
 * @date 2025-10-28
 * @author
 * Project Teams
 */

#include "TropicalStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

/**
 * @brief Applies watering behavior appropriate for tropical plants.
 * 
 * Tropical species require high moisture levels to thrive. Watering is
 * applied generously, but excessive saturation reduces health to reflect
 * the effects of poor drainage or waterlogging.
 * 
 * @param plant Reference to the tropical plant being watered.
 */

void TropicalStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;

    double waterAmount = 20 + (species->getWaterSensitivity() * 10);
    plant.addWater(static_cast<int>(waterAmount));
    
    if (plant.getMoisture() > 100)
    {
        plant.addHealth(-5);
    }
}

/**
 * @brief Applies fertilizer effects suited for tropical growth patterns.
 * 
 * Fertilization promotes vigorous growth and recovery, scaled by the
 * plant’s species growth rate. It is most effective when overall health
 * is below an ideal range, encouraging sustainable regeneration.
 * 
 * @param plant Reference to the tropical plant being fertilized.
 */

void TropicalStrategy::fertilize(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;

    int healthBoost = 8 + static_cast<int>(species->getGrowthRate() * 5);
    if (plant.getHealth() < 60) 
    {
        plant.addHealth(healthBoost);
    }
}

/**
 * @brief Applies insecticide treatment for tropical species.
 * 
 * Tropical plants are more tolerant to chemical treatments due to their
 * dense foliage and humid environment. Insecticide is applied in higher
 * amounts but still penalizes excessive use to simulate toxicity stress.
 * 
 * @param plant Reference to the tropical plant being treated.
 */

void TropicalStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int insecticideAmount = 20 + static_cast<int>(species->getInsecticideTolerance() * 10);
    plant.addInsecticide(insecticideAmount);
    
    if (plant.getInsecticide() > 100) 
    {
        plant.addHealth(-4);
    } 
    else 
    {
        plant.addHealth(2);
    }
}