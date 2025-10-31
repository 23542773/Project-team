#include "TropicalStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

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