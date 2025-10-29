#ifndef INDOORFACTORY_H
#define INDOORFACTORY_H
#include "PlantKitFactory.h"
#include "CeramicPot.h"
#include "LightAirySoilMix.h"
#include "CareStrategy.h"
#include "IndoorStrategy.h"

class IndoorFactory : public PlantKitFactory
{
	//Maybe should make strategy singleton class idk
	static IndoorStrategy s;

public:

	CareStrategy* careStrategy() override;

protected:

	Pot* createPot() override;

	SoilMix* createSoilMix() override;
};

#endif
