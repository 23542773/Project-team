#ifndef SANDYSOILMIX_H
#define SANDYSOILMIX_H
#include "SoilMix.h"

class SandySoilMix : public SoilMix
{


public:

	SandySoilMix() : SoilMix(35) {}
	std::string name() override { return "Sandy Soil Mix"; }
	SoilMix* clone() override { return new SandySoilMix(*this); }
};

#endif
