#ifndef PEATSOILMIX_H
#define PEATSOILMIX_H
#include "SoilMix.h"

class PeatSoilMix : public SoilMix
{
public:

	PeatSoilMix();
	std::string name() override;
	SoilMix* clone() const override;
};

#endif
