#include "WetlandStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

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