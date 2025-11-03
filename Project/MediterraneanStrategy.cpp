/**
 * @file MediterraneanStrategy.cpp
 * @brief Implements the MediterraneanStrategy class for plant care in temperate climates.
 * 
 * This strategy defines care routines for plants adapted to Mediterranean conditions,
 * emphasizing balanced watering, nutrient-rich fertilization, and moderate insecticide
 * use to simulate mild, seasonal environments with periodic dry spells.
 * 
 * @date 2025-10-28
 * @author
 * Project Teams
 */

#include "MediterraneanStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

/**
 * @brief Applies watering behavior suitable for Mediterranean plants.
 * 
 * Mediterranean species thrive under periodic but balanced watering.
 * Water is added in moderate amounts, while overwatering reduces plant
 * health to simulate sensitivity to excess soil moisture.
 * 
 * @param plant Reference to the Mediterranean plant being watered.
 */

void MediterraneanStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    int add = static_cast<int>(15 + (species->getWaterSensitivity() * 8));
    const int before = plant.getMoisture();
    const int projected = before + add;

    if (projected > 100)
    {
        plant.addHealth(-5);
    }

    plant.addWater(add);
}

/**
 * @brief Applies fertilizer effects suitable for Mediterranean plant growth.
 * 
 * Fertilization supports strong but steady growth, scaling with the species’
 * natural growth rate. Plants benefit most when their health is below optimal
 * levels, encouraging gradual recovery and resilience.
 * 
 * @param plant Reference to the Mediterranean plant being fertilized.
 */

void MediterraneanStrategy::fertilize(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int healthBoost = 6 + static_cast<int>(species->getGrowthRate() * 4);
    if (plant.getHealth() < 60) 
    {
        plant.addHealth(healthBoost);
    }
}

/**
 * @brief Applies insecticide treatment balanced for Mediterranean species.
 * 
 * Insecticide is applied moderately, taking into account each species’
 * tolerance to chemical treatment. Proper dosage enhances plant health,
 * while overapplication decreases it to reflect environmental stress.
 * 
 * @param plant Reference to the Mediterranean plant being treated.
 */

void MediterraneanStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int add = 16 + static_cast<int>(species->getInsecticideTolerance() * 8);
    const int before = plant.getInsecticide();
    const int projected = before + add;
    if (projected > 100) 
    {
        plant.addHealth(-4);
    }
    plant.addInsecticide(add); 
}