#ifndef CERAMICPOT_H
#define CERAMICPOT_H
#include "Pot.h"

class CeramicPot : public Pot
{
public:

	CeramicPot();
	std::string name() override;
	Pot* clone() const override;
};

#endif
