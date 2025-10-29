#ifndef POT_H
#define POT_H
#include <iostream>
#include <string>

class Pot 
{

	int cost;

public:

	Pot(int c) : cost(c) {}
	virtual ~Pot() = default;
	virtual std::string name() = 0;
	int getCost() { return cost; }
	virtual Pot* clone() = 0;
};

#endif
