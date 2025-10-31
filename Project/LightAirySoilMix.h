#ifndef LIGHTAIRYSOILMIX_H
#define LIGHTAIRYSOILMIX_H
#include "SoilMix.h"

class LightAirySoilMix : public SoilMix
{

public:

	LightAirySoilMix();
	std::string name() override;
	SoilMix* clone() const override;
};

#endif
