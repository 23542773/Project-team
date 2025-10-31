#ifndef INDOORSTRATEGY_H
#define INDOORSTRATEGY_H

#include "CareStrategy.h"

class IndoorStrategy : public CareStrategy 
{
public:
    void water(Plant& plant) override;
    void fertilize(Plant& plant) override;
    void sprayInsecticide(Plant& plant) override;
};

#endif