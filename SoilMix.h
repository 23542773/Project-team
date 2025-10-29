#ifndef SOILMIX_H
#define SOILMIX_H
#include <iostream>
#include <string>

class SoilMix 
{

	int cost;

public:

	SoilMix(int c = 0) : cost(c) {}
    virtual ~SoilMix() = default;
    virtual std::string name() = 0;
    int getCost() { return cost; }
	virtual SoilMix* clone() = 0;
};

#endif
