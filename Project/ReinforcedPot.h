#ifndef REINFORCEDPOT_H
#define REINFORCEDPOT_H
#include "SaleDecorator.h"
#include <string>

class ReinforcedPot : public SaleDecorator 
{
public:

    explicit ReinforcedPot(std::unique_ptr<SaleItem> inner);
    double cost() override;
    std::string description() override;
};

#endif