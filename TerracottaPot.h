#ifndef TROPICALFACTORY_H
#define TROPICALFACTORY_H
#include "PlantKitFactory.h"
#include "GlazedCeramicPot.h"
#include "PeatSoilMix.h"
#include "CareStrategy.h"
#include "TropicalStrategy.h"

class TropicalFactory : public PlantKitFactory
{
	//Maybe should make strategy singleton class idk
	static TropicalStrategy s;

public:

	CareStrategy* careStrategy() override;

protected:

	Pot* createPot() override;

	SoilMix* createSoilMix() override;
};

#endif
