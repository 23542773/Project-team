#ifndef GRITTYLIMESOILMIX_H
#define GRITTYLIMESOILMIX_H
#include "SoilMix.h"

class GrittyLimeSoilMix : public SoilMix
{

public:

	GrittyLimeSoilMix() : SoilMix(120) {}
	std::string name() override { return "Gritty Lime Soil Mix"; }
	SoilMix* clone() override { return new GrittyLimeSoilMix(*this); }
};

#endif
