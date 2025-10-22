#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H
#include "Plant.h"

class CareStrategy {


public:
	virtual void water(Plant& p) = 0;
};

#endif
