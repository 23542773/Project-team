#ifndef WETLANDFACTORY_H
#define WETLANDFACTORY_H
#include "PlantKitFactory.h"
#include "AquaticBasketPot.h"
#include "AquaticSoilMix.h"
#include "CareStrategy.h"
#include "WetlandStrategy.h"

class WetlandFactory : public PlantKitFactory
{
	//Maybe should make strategy singleton class idk
	static WetlandStrategy s;

public:

	CareStrategy* careStrategy() override;

protected:

	Pot* createPot() override;

	SoilMix* createSoilMix() override;
};

#endif
