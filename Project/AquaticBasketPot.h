#ifndef AQUATICBASKETPOT_H
#define AQUATICBASKETPOT_H
#include "Pot.h"

class AquaticBasketPot : public Pot
{


public:

	AquaticBasketPot();
	std::string name() override;
	Pot* clone() const override;
};

#endif
