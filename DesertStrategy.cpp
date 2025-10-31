#include "DesertStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

void DesertStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    double waterAmount = 10 + ((1.0 - species->getWaterSensitivity()) * 10);
    plant.addWater(static_cast<int>(waterAmount));
    if (plant.getMoisture() > 100) 
    {
        plant.addHealth(-5);
    }
}

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

void DesertStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int insecticideAmount = 12 + static_cast<int>(species->getInsecticideTolerance() * 8);
    plant.addInsecticide(insecticideAmount);
    
    if (plant.getInsecticide() > 100) 
    {
        plant.addHealth(-4);
    }
}