#ifndef TERRACOTTAPOT_H
#define TERRACOTTAPOT_H
#include "Pot.h"
class TerracottaPot : public Pot
{

public:
	
	TerracottaPot();
	std::string name() override;
	Pot* clone() const override;
};

#endif

