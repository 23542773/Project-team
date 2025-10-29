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
    virtual std::string name() const = 0;
    int getCost() const { return cost; }
	virtual SoilMix* clone() const = 0;
};

#endif
