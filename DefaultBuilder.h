#ifndef DEFAULTBUILDER_H
#define DEFAULTBUILDER_H

#include "PackageBuilder.h"

#include <iostream>

class DefualtBuilder: public PackageBuilder{
private:
CustomPlantPackage pkg;
public: 
DefualtBuilder();
void reset();

void BuildPlant(PlantFactory& f, std::string id );

void buildPot(PlantFactory& f);

void buildSoil(PlantFactory& f);

CustomPlantPackage getResult();
};

#endif // DEFAULTBUILDER_H