#ifndef AQUATICSOILMIX_H
#define AQUATICSOILMIX_H
#include "SoilMix.h"

class AquaticSoilMix : public SoilMix
{

public:

	AquaticSoilMix() : SoilMix(80) {}
	std::string name() override { return "Aquatic Soil Mix"; }
	SoilMix* clone() override { return new AquaticSoilMix(*this); }
};

#endif
