#ifndef PLANT_H
#define PLANT_H

#include <iostream>

// #include "SoilMix.h"
// #include "Pot.h"
// #include "CareStrategy.h"
#include "PlantState.h"
// #include "PlantFlyweight.h"

struct Biome {
    std::string name;
    double temp;   // °C
    double humidity;      // %
    float waterPerDay;     // How often to water (in days)
};

class PlantState;

class Plant {

    std::string id;
    std::string colour;
    std::string name;
    Biome biome;
    // PlantFlyweight species;
    //CareStrategy care;
    PlantState* state;
    // SoilMix* soil;
	// Pot* pot;

    int health = 100;

    float ageInDays=0;
    float moistureLevel=0;
    float humidity = 0;
    float temp = 0;
    float height = 0.0;
    float rootDepth = 0.0;
    float lightExp = 0.0;//?

    float soilPh = 0.0;
    float costPerDay = 0.0;//R -??currencies
    

    public:
        Plant();
        virtual ~Plant();
        Plant(const Plant& other);
        Plant* clone(std::string plantId, std::string colour);
    
        void water();
        void fertilize();
        void tickDay();
        void addWater(int amount);
        void addHealth(int amount);
        void setState(PlantState* s);

        Biome getBiome();

        int getHealth();

        float getCost();
        float getAgeDays();
        float getMoisture();

        std::string getID();
        // std::string sku();//?
        std::string getName();
        std::string getColour();

        // PlantFlyweight* getSpeciesFly();
        // SoilMix* getSoilMix();
        // Pot* getPot();
        // CareStrategy* getCareStrategy();
        // PlantState* getPlantState();
};

#endif//PLANT_H