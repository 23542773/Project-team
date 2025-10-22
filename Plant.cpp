#include "Plant.h"

Plant::Plant(const std::string& id, PlantFlyweight* sf,Pot* p, SoilMix* s)
    : id(id), species(sf), pot(p), soilMix(s) {}


    Plant::~Plant() {
    delete pot;
    delete soilMix;
}

void Plant::water(){}
void Plant::tickDay(){}
//void Plant::setState(PlantState state){}
void Plant::fertillize(){}

std::string Plant::getId() const {
    return id;
}

int Plant::getCost() const {
    return (species ? species->getCost() : 0)
         + (pot ? pot->getCost() : 0)
         + (soilMix ? soilMix->getCost() : 0);
}
