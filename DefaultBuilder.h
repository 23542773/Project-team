#ifndef DEFAULTBUILDER_H
#define DEFAULTBUILDER_H

#include "PackageBuilder.h"

#include <iostream>

class DefaultBuilder: public PackageBuilder{
private:
CustomPlantPackage pkg;
public: 
DefaultBuilder();
void reset();

void BuildPlant(PlantKitFactory& f, std::string id );

void buildPot(PlantKitFactory& f);

void buildSoil(PlantKitFactory& f);

CustomPlantPackage* getResult();
};

#endif // DEFAULTBUILDER_H