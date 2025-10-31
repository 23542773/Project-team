#include "GlazedCeramicPot.h"

GlazedCeramicPot::GlazedCeramicPot() : Pot(400) {}

std::string GlazedCeramicPot::name() 
{ 
    return "Glazed Ceramic Pot"; 
}

Pot* GlazedCeramicPot::clone()  const
{ 
    return new GlazedCeramicPot(*this); 
}