#ifndef SPECIESFLYWEIGHT_H
#define SPECIESFLYWEIGHT_H

#include "PlantFlyweight.h"

class SpeciesFlyweight: public PlantFlyweight {

private:
	std::string name;
	std::string env;
	CarePresets cc;

public:
	std::string speciesName();

	std::string envType();

	CarePresets careDefaults();
};

#endif
