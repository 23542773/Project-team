#ifndef TROPICALSTRATEGY_H
#define TROPICALSTRATEGY_H

#include "CareStrategy.h"

class TropicalStrategy : public CareStrategy 
{
public:
    void water(Plant& plant) override;
    void fertilize(Plant& plant) override;
    void sprayInsecticide(Plant& plant) override;
};

#endif 