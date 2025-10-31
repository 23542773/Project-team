#ifndef GRITTYLIMESOILMIX_H
#define GRITTYLIMESOILMIX_H
#include "SoilMix.h"

class GrittyLimeSoilMix : public SoilMix
{

public:

	GrittyLimeSoilMix();
	std::string name() override;
	SoilMix* clone() const override;
};

#endif
