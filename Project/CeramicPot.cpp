#include "CeramicPot.h"

CeramicPot::CeramicPot() : Pot(200) {}

std::string CeramicPot::name() 
{
     return "Ceramic Pot"; 
    }

Pot* CeramicPot::clone() const
{ 
    return new CeramicPot(*this); 
}	