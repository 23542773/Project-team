#ifndef MEDITERRANEANFACTORY_H
#define MEDITERRANEANFACTORY_H
#include "PlantKitFactory.h"
#include "UnglazedClayPot.h"
#include "GrittyLimeSoilMix.h"
#include "CareStrategy.h"
#include "MediterraneanStrategy.h"

class MediterraneanFactory : public PlantKitFactory
{
	//Maybe should make strategy singleton class idk
	static MediterraneanStrategy s;

public:

	CareStrategy* careStrategy() override;

protected:

	Pot* createPot() override;

	SoilMix* createSoilMix() override;
};

#endif
