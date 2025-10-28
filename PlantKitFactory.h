#ifndef PLANTKITFACTORY_H
#define PLANTKITFACTORY_H
#include <string>
#include "Pot.h"
#include "SoilMix.h"
#include "Plant.h"
#include "PlantState.h"
#include "SeedlingState.h"
#include "PlantFlyweight.h"
#include "CareStrategy.h"

class PlantKitFactory 
{

public:

	Plant* createPlant(std::string id, std::string colour, PlantFlyweight* sf);
	//Public for now but if we want to enforce no more than one concrete strategy each, singleton should be used
	virtual CareStrategy* careStrategy() = 0;

protected:

	virtual Pot* createPot() = 0;

	virtual SoilMix* createSoilMix() = 0;
};

#endif
