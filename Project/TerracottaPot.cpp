#include "TerracottaPot.h"

TerracottaPot::TerracottaPot() : Pot(90) {}

std::string TerracottaPot::name()  
{
     return "Terracotta Pot"; 
}

Pot* TerracottaPot::clone() const
{ 
    return new TerracottaPot(*this); 
}
