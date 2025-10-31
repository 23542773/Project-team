#include "MessageCard.h"

MessageCard::MessageCard(std::unique_ptr<SaleItem> inner, std::string msg): SaleDecorator(std::move(inner)), msg(msg) {}

double MessageCard::cost() 
{ 
    return getInnerComp().cost() + 15.0; 
}

std::string MessageCard::description() 
{
    return getInnerComp().description() + " + Card(" + msg + ")";
}