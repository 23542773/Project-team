#include "DefaultBuilder.h"
//concreteBuilder
//maybe have a constructor and get the Plantfactory instead of passing in the whole time

DefaultBuilder::DefaultBuilder(){
    
}

void DefaultBuilder::reset(){
    //paass in elements of nullptr to CustomPackage
    //add checks in getResult
}

void DefaultBuilder::BuildPlant(PlantKitFactory& f, std::string id ){
    PlantFlyweight* species = /* obtain or create appropriate Flyweight */;
    Plant* p = f.createPlant(id, species);
    pkg.setPlant(p);
}

void DefaultBuilder::buildPot(PlantKitFactory& f){
    Pot* p = f.createPot();
    pkg.setPot(p);
}

void DefaultBuilder::buildSoil(PlantKitFactory& f){
    SoilMix* s = f.createSoilMix();
    pkg.setSoilMix(s);
}

CustomPlantPackage DefaultBuilder::getResult(){
    return &pkg;
}

void DefaultBuilder::reset() {
    pkg = CustomPlantPackage(); 
}

