#ifndef SANDYSOILMIX_H
#define SANDYSOILMIX_H
#include "SoilMix.h"

class SandySoilMix : public SoilMix
{


public:

	SandySoilMix();
	std::string name() override;
	SoilMix* clone() const override;
};

#endif
