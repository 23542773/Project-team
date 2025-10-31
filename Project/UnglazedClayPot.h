#ifndef UNGLAZEDCLAYPOT_H
#define UNGLAZEDCLAYPOT_H
#include "Pot.h"

class UnglazedClayPot : public Pot
{
public:

	UnglazedClayPot();
	std::string name() override;
	Pot* clone() const override;
};

#endif
