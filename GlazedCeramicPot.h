#ifndef GLAZEDCERAMICPOT_H
#define GLAZEDCERAMICPOT_H
#include "Pot.h"

class GlazedCeramicPot : public Pot
{

public:

	GlazedCeramicPot() : Pot(400) {}
	std::string name() override { return "Glazed Ceramic Pot"; }
	Pot* clone() override { return new GlazedCeramicPot(*this); }
};

#endif

