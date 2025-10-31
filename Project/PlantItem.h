#ifndef PLANTITEM_H
#define PLANTITEM_H
#include "SaleItem.h"
#include "Plant.h"

class PlantItem : public SaleItem 
{
public:

    PlantItem(Plant* p);
    double cost() override;
    std::string description() override; 

private:

    Plant* plant; 
};

#endif