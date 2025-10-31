#ifndef DESERTFACTORY_H
#define DESERTFACTORY_H
#include "PlantKitFactory.h"
#include "TerracottaPot.h"
#include "SandySoilMix.h"
#include "CareStrategy.h"
#include "DesertStrategy.h"

class DesertFactory : public PlantKitFactory
{
	//Maybe should make strategy singleton class idk
	static DesertStrategy s;

public:

	CareStrategy* careStrategy() override;

protected:

	Pot* createPot() override;

	SoilMix* createSoilMix() override;


};

#endif
