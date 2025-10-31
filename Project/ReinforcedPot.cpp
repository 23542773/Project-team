#include "ReinforcedPot.h"

ReinforcedPot::ReinforcedPot(std::unique_ptr<SaleItem> inner) : SaleDecorator(std::move(inner)) {}

double ReinforcedPot::cost()  
{ 
    return getInnerComp().cost() + 80.0; 
}

std::string ReinforcedPot::description()  
{
    return getInnerComp().description() + " + Reinforced Pot";
}