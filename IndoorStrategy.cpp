#include "IndoorStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

void IndoorStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    double waterAmount = 18 + (species->getWaterSensitivity() * 7);
    plant.addWater(static_cast<int>(waterAmount)); 
    
    if (plant.getMoisture() > 100) 
    {
        plant.addHealth(-5);
    }
}

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

void IndoorStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;    

    int insecticideAmount = 12 + static_cast<int>(species->getInsecticideTolerance() * 6);
    plant.addInsecticide(insecticideAmount);   
    
    if (plant.getInsecticide() > 100) 
    {
        plant.addHealth(-4);
    } 
    else
    {
        plant.addHealth(3);
    }
}