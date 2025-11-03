/**
 * @file IndoorStrategy.cpp
 * @brief Implements the IndoorStrategy class for indoor plant care.
 * 
 * This strategy defines care behavior for indoor plants, focusing on
 * moderate watering, balanced fertilization, and careful insecticide
 * application to suit species commonly grown in controlled environments.
 * 
 * @date 2025-10-28
 * @author
 * Project Teams
 */

#include "IndoorStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

/**
 * @brief Applies watering behavior suitable for indoor plants.
 * 
 * Indoor species require consistent but moderate watering to maintain
 * stable moisture levels. Overwatering reduces health, simulating the
 * effects of root saturation in confined environments.
 * 
 * @param plant Reference to the indoor plant being watered.
 */

void IndoorStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int add = static_cast<int>(18 + (species->getWaterSensitivity() * 7));
    const int before = plant.getMoisture();
    const int projected = before + add;
    if (projected > 100)
    {
        plant.addHealth(-5);
    }
    plant.addWater(add);
}

/**
 * @brief Applies fertilizer effects optimized for indoor growth.
 * 
 * Fertilization supports gradual health recovery and growth, scaled by
 * the species’ natural growth rate. It benefits plants most when overall
 * health is below an ideal threshold.
 * 
 * @param plant Reference to the indoor plant being fertilized.
 */

void IndoorStrategy::fertilize(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int healthBoost = 5 + static_cast<int>(species->getGrowthRate() * 4);
    if (plant.getHealth() < 60) 
    {
        plant.addHealth(healthBoost);
    }
}

/**
 * @brief Applies insecticide treatment suitable for indoor environments.
 * 
 * Insecticide application balances pest control with plant health, adjusted
 * according to the species’ tolerance level. Proper use improves health,
 * while excessive application reduces it to reflect chemical stress.
 * 
 * @param plant Reference to the indoor plant being treated.
 */

void IndoorStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;    

    int add = 12 + static_cast<int>(species->getInsecticideTolerance() * 6);
    const int before = plant.getInsecticide();
    const int projected = before + add;
    if (projected > 100) 
    {
        plant.addHealth(-4);
    } 
    plant.addInsecticide(add);
}