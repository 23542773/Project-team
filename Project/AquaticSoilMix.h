#ifndef AQUATICSOILMIX_H
#define AQUATICSOILMIX_H
#include "SoilMix.h"

class AquaticSoilMix : public SoilMix
{

public:

	AquaticSoilMix();
	std::string name() override;
	SoilMix* clone() const override;
};

#endif
