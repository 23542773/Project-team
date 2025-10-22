#include "CustomPlantPackage.h"
//product

    void CustomPlantPackage::setSoilMix(SoilMix* s){
        soil = s;
    }

    void CustomPlantPackage::setPlant(Plant* p){
        plant = p;
    }

    void CustomPlantPackage::setPot(Pot* p){
        pot = p;
    }