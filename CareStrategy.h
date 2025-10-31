#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H
#include "Plant.h"

class Plant;

class CareStrategy 
{


public:

	virtual ~CareStrategy() = default;
    virtual void water(Plant& plant) = 0;
    virtual void fertilize(Plant& plant) = 0;
    virtual void sprayInsecticide(Plant& plant) = 0;
};

#endif
