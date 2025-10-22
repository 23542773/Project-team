#ifndef PLANT_H
#define PLANT_H

#include <iostream>

class PlantState;

class Plant {

    std::string id;
    //PlantFlyweight species;
    //CareStrategy care;
    //PlantState state;
    int ageInDays;
    int moistureLevel;
    PlantState* state;

    public:
        Plant();
        virtual ~Plant();
    
        void water();
        void fertilize();
        void tickDay();
        void setState(PlantState* s);
};

#endif//PLANT_H