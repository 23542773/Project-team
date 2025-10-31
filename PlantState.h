#ifndef PLANTSTATE_H
#define PLANTSTATE_H
#include <string>
#include "Plant.h"

class Plant;

class PlantState 
{

public:

	virtual ~PlantState() = default;
    virtual void checkChange(Plant& plant) = 0;
    virtual std::string name() = 0;
    virtual bool isMature() { return false; }
};

#endif
