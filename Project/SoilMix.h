#ifndef SOILMIX_H
#define SOILMIX_H
#include <iostream>
#include <string>

class SoilMix 
{

	int cost;

public:

	SoilMix(int c);
    virtual ~SoilMix() = default;
    virtual std::string name() = 0;
    int getCost() const;
	virtual SoilMix* clone() const = 0;
};

#endif
