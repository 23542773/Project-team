#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "PlantFlyweight.h" 
#include "Pot.h"
#include "SoilMix.h"

class Plant{

    private:
        std::string id;
        PlantFlyweight* species;
        //CareStrategy care; //Still needs to be implemented
        //PlantState state; //Still needs to be implemented
        int ageInDays;
        int moistureLevel;
        Pot* pot;
        SoilMix* soilMix;
    public:
        Plant(const std::string& id, PlantFlyweight* sf,Pot* p, SoilMix* s);
        virtual ~Plant();
        void water();
        void tickDay();
        //void setState(PlantState state);
        void fertillize();
        std::string getId() const;
        int getCost();
};

#endif