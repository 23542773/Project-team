#ifndef GLAZEDCERAMICPOT_H
#define GLAZEDCERAMICPOT_H
#include "Pot.h"

class GlazedCeramicPot : public Pot
{

public:

	GlazedCeramicPot();
	std::string name() override;
	Pot* clone() const override;
};

#endif

