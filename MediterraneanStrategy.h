#ifndef MEDITERRANEANSTRATEGY_H
#define MEDITERRANEANSTRATEGY_H

#include "CareStrategy.h"

class MediterraneanStrategy : public CareStrategy 
{
public:

    void water(Plant& plant) override;
    void fertilize(Plant& plant) override;
    void sprayInsecticide(Plant& plant) override;
};

#endif