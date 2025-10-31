#include "MediterraneanStrategy.h"
#include "Plant.h"
#include "PlantFlyweight.h"

void MediterraneanStrategy::water(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    double waterAmount = 15 + (species->getWaterSensitivity() * 8);
    plant.addWater(static_cast<int>(waterAmount));
    
    if (plant.getMoisture() > 100) 
    {
        plant.addHealth(-5);
    }
}

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

void MediterraneanStrategy::sprayInsecticide(Plant& plant) 
{
    PlantFlyweight* species = plant.getSpeciesFly();
    if (!species) return;
    
    int insecticideAmount = 16 + static_cast<int>(species->getInsecticideTolerance() * 8);
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