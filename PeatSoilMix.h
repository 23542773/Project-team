#ifndef PEATSOILMIX_H
#define PEATSOILMIX_H
#include "SoilMix.h"

class PeatSoilMix : public SoilMix
{
public:

	PeatSoilMix() : SoilMix(50) {}
	std::string name() override { return "Peat Soil Mix"; }
	SoilMix* clone() override { return new PeatSoilMix(*this); }
};

#endif
