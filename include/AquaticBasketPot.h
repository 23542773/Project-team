#ifndef AQUATICBASKETPOT_H
#define AQUATICBASKETPOT_H
#include "Pot.h"

class AquaticBasketPot : public Pot
{


public:

	AquaticBasketPot() : Pot(250) {}
	std::string name() override { return "Aquatic Basket Pot"; }
	Pot* clone() override { return new AquaticBasketPot(*this); }
};

#endif
