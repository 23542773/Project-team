#include "AquaticBasketPot.h"

AquaticBasketPot::AquaticBasketPot() : Pot(250) {}

std::string AquaticBasketPot::name()  
{
    return "Aquatic Basket Pot"; 
}
Pot* AquaticBasketPot::clone() const  
{ 
    return new AquaticBasketPot(*this); 
}