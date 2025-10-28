#ifndef LIGHTAIRYSOILMIX_H
#define LIGHTAIRYSOILMIX_H
#include "SoilMix.h"

class LightAirySoilMix : public SoilMix
{

public:

	LightAirySoilMix() : SoilMix(90) {}
	std::string name() override { return "Light Airy Soil Mix"; }
	SoilMix* clone() override { return new LightAirySoilMix(*this); }
};

#endif
