#ifndef UNSHAREDSPECIESFLYWEIGHT_H
#define UNSHAREDSPECIESFLYWEIGHT_H

#include "PlantFlyweight.h"

class UnsharedSpeciesFlyweight: public PlantFlyweight {

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
