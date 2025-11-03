/**
 * @file DesertStrategy.cpp
 * @brief Implements the DesertStrategy class for desert-adapted plants.
 * 
 * This strategy defines plant care behavior specific to desert species,
 * emphasizing minimal watering, cautious fertilization, and moderate
 * insecticide use to reflect their natural tolerance and growth patterns.
 * 
 * @date 2025-10-28
 * @author
 * Project Teams
 */

#include "DesertStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

/**
 * @brief Applies watering behavior appropriate for desert plants.
 * 
 * Desert species are drought-tolerant and receive water only when
 * moisture levels are critically low. Excess watering can reduce
 * health, simulating root damage from oversaturation.
 * 
 * @param plant Reference to the desert plant being watered.
 */

void DesertStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int add = static_cast<int>(10 + ((1.0 - species->getWaterSensitivity()) * 10));
    const int before = plant.getMoisture();
    const int projected = before + add;
    if (projected > 100)
    {
        plant.addHealth(-5);
    }
    plant.addWater(add);
}

/**
 * @brief Applies fertilizer effects suitable for desert plant growth.
 * 
 * Fertilization provides a small health boost depending on the plant’s
 * growth rate and current condition. Desert species benefit most when
 * health is below an optimal threshold.
 * 
 * @param plant Reference to the desert plant being fertilized.
 */

void DesertStrategy::fertilize(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int healthBoost = 3 + static_cast<int>(species->getGrowthRate() * 4);
    if (plant.getHealth() < 60) 
    {
        plant.addHealth(healthBoost);
    }
}

/**
 * @brief Applies insecticide treatment tuned for desert plant tolerance.
 * 
 * Adds a moderate amount of insecticide based on the plant’s species
 * tolerance. Excessive spraying negatively impacts health to simulate
 * chemical stress or toxicity.
 * 
 * @param plant Reference to the desert plant being treated.
 */

void DesertStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int add = 12 + static_cast<int>(species->getInsecticideTolerance() * 8);
    const int before = plant.getInsecticide();
    const int projected = before + add;
    if (projected > 100)
    {
        plant.addHealth(-4);
    }
    plant.addInsecticide(add);
}