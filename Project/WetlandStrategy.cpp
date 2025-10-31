/**
 * @file WetlandStrategy.cpp
 * @brief Implements the WetlandStrategy class for wetland plant care.
 * 
 * This strategy defines care behavior for wetland and aquatic-adapted plants,
 * focusing on frequent watering, nutrient-dense fertilization, and careful
 * pest management to reflect the water-rich environments these species inhabit.
 * 
 * @date 2025-10-28
 * @author
 * Project Teams
 */

#include "WetlandStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

/**
 * @brief Applies watering behavior appropriate for wetland plants.
 * 
 * Wetland species thrive in highly moist environments and receive generous
 * watering to maintain saturated conditions. Overwatering still reduces health
 * to simulate stagnation or oxygen deprivation effects.
 * 
 * @param plant Reference to the wetland plant being watered.
 */

void WetlandStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    double waterAmount = 25 + (species->getWaterSensitivity() * 12);
    plant.addWater(static_cast<int>(waterAmount)); 
    
    if (plant.getMoisture() > 100) 
    {
        plant.addHealth(-5);
    }
}

/**
 * @brief Applies fertilizer effects suited for wetland species.
 * 
 * Fertilization boosts growth and recovery in nutrient-rich environments.
 * The benefit scales with the plant’s growth rate and is most effective
 * when overall health is below an optimal range.
 * 
 * @param plant Reference to the wetland plant being fertilized.
 */

void WetlandStrategy::fertilize(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int healthBoost = 10 + static_cast<int>(species->getGrowthRate() * 6);
    if (plant.getHealth() < 60) 
    {
        plant.addHealth(healthBoost);
    }
}

/**
 * @brief Applies insecticide treatment tuned for wetland environments.
 * 
 * Wetland plants generally require moderate pest control. Insecticide
 * application considers the species’ tolerance, providing slight health
 * improvement when used appropriately and penalizing overuse to reflect
 * chemical or ecological stress.
 * 
 * @param plant Reference to the wetland plant being treated.
 */

void WetlandStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int insecticideAmount = 25 + static_cast<int>(species->getInsecticideTolerance() * 10);
    plant.addInsecticide(insecticideAmount);  
    
    if (plant.getInsecticide() > 100) 
    {
        plant.addHealth(-4);
    } 
    else 
    {
        plant.addHealth(1);
    }
}