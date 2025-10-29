#ifndef UNGLAZEDCLAYPOT_H
#define UNGLAZEDCLAYPOT_H
#include "Pot.h"

class UnglazedClayPot : public Pot
{
public:

	UnglazedClayPot() : Pot(70) {}
	std::string name() override { return "Unglazed Clay Pot"; }
	Pot* clone() override { return new UnglazedClayPot(*this); }
};

#endif
