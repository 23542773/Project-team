#include "PlantItem.h"

PlantItem::PlantItem(Plant* p) : plant(p) {}

double PlantItem::cost() 
{
    return plant->cost();
}
std::string PlantItem::description()
{
    return plant->name(); 
}
