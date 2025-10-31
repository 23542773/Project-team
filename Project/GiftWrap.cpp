#include "GiftWrap.h"

GiftWrap::GiftWrap(std::unique_ptr<SaleItem> inner) : SaleDecorator(std::move(inner)) {}

double GiftWrap::cost()  
{ 
    return getInnerComp().cost() + 25.0; 
}

std::string GiftWrap::description()  
{
    return getInnerComp().description() + " + Gift Wrap";
}