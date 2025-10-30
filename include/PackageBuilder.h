#ifndef PACKAGEBUILDER_H
#define PACKAGEBUILDER_H

#include "CustomPlantPackage.h"
#include "PlantKitFactory.h"

#include <iostream>

class PackageBuilder{
    public: 
    virtual void reset() = 0;

    virtual void BuildPlant(PlantKitFactory& f, std::string id ) = 0;

    virtual void buildPot(PlantKitFactory& f) = 0;

    virtual void buildSoil(PlantKitFactory& f) = 0;

    virtual CustomPlantPackage* getResult() = 0;
};

#endif 