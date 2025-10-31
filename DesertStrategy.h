#ifndef DESERTSTRATEGY_H
#define DESERTSTRATEGY_H

#include "CareStrategy.h"

class DesertStrategy : public CareStrategy 
{
public:

	void water(Plant& plant) override;
    void fertilize(Plant& plant) override;
    void sprayInsecticide(Plant& plant) override;
};

#endif