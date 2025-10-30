#ifndef CUSTOMPLANTPACKAGE_H
#define CUSTOMPLANTPACKAGE_H


#include "Plant.h"
#include "Pot.h"
#include "SoilMix.h"

class CustomPlantPackage{
    private:
        Plant* plant;
        Pot* pot;
        SoilMix* soil;
    public:
        void setPlant(Plant* p);
        void setPot(Pot* p);
        void setSoilMix(SoilMix* s);
        Plant* getPlant() const;
        Pot* getPot() const;
        SoilMix* getSoilMix() const;

};

#endif 