#ifndef POT_H
#define POT_H
#include <iostream>
#include <string>

class Pot 
{

	int cost;

public:

	Pot(int c);
	virtual ~Pot() = default;
	virtual std::string name() = 0;
	int getCost();
	virtual Pot* clone() const = 0;
};

#endif
