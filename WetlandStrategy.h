#ifndef WETLANDSTRATEGY_H
#define WETLANDSTRATEGY_H

#include "CareStrategy.h"

class WetlandStrategy : public CareStrategy 
{
public:

    void water(Plant& plant) override;
    void fertilize(Plant& plant) override;
    void sprayInsecticide(Plant& plant) override;
};

#endif