#ifndef PLANTFLYWEIGHT_H
#define PLANTFLYWEIGHT_H

#include <iostream>

#include "CarePresets.h"

class PlantFlyweight {


public:
	virtual std::string speciesName() = 0;

	virtual std::string envType() = 0;

	virtual CarePresets careDefaults() = 0;
};

#endif
