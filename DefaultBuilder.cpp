#include "DefaultBuilder.h"
//concreteBuilder
//maybe have a constructor and get the Plantfactory instead of passing in the whole time

DefualtBuilder::DefualtBuilder(){
    
}

void DefualtBuilder::reset(){
    //paass in elements of nullptr to CustomPackage
    //add checks in getResult
}

void DefualtBuilder::BuildPlant(PlantFactory& f, std::string id ){
//    Plant* p =  f->createPlant(id, ); call factory createPlant method
//    pkg->setPlant(p); call CustomPackage setter
}

void DefualtBuilder::buildPot(PlantFactory& f){
    Pot* p = f->createPot();
    // pkg->setPot(p); call CustomPackage pot setter
}

void DefualtBuilder::buildSoil(PlantFactory& f){
    SoilMix* s = f->createSoilMix();
    //call CustomPackage Soil Setter
}

CustomPlantPackage DefualtBuilder::getResult(){
    //call the CustomPackage getResult method
}
