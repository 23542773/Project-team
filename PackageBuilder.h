#ifndef PACKAGEBUILDER_H
#define PACKAGEBUILDER_H

#include "CustomPlantPackage.h"
//#include "PlantFactory.h"

#include <iostream>

class PackageBuilder{
    public: 
    virtual void reset();

    virtual void BuildPlant(PlantFactory& f, std::string id ) = 0;

    virtual void buildPot(PlantFactory& f) = 0;

    virtual void buildSoil(PlantFactory& f) = 0;

    virtual CustomPlantPackage getResult() = 0;
};

#endif // PACKAGEBUILDER_H