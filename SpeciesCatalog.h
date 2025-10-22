#ifndef SPECIESCATALOG_H
#define SPECIESCATALOG_H

#include <iostream>
#include <map>

#include "SpeciesKey.h"
#include "CarePresets.h"

class PlantFlyweight;

class SpeciesCatalog {

private:
	std::map<SpeciesKey, PlantFlyweight*> pool;

public:
	PlantFlyweight* get(SpeciesKey& s);

	PlantFlyweight* createUnshared(std::string n, std::string env, CarePresets cc);

	void registerSpecies(SpeciesKey& s, std::string env, CarePresets cc);
};

#endif
