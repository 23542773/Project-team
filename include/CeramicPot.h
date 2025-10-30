#ifndef CERAMICPOT_H
#define CERAMICPOT_H
#include "Pot.h"

class CeramicPot : public Pot
{
public:

	CeramicPot() : Pot(200) {}
	std::string name() override { return "Ceramic Pot"; }
	Pot* clone() override { return new CeramicPot(*this); }	
};

#endif
