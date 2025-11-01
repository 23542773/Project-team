#include "CustomerDash.h"

void CustomerDash::onEvent(events::Plant e)  
{
    if (e.type == events::PlantType::Matured) maturedIds.push_back(e.plantId);
}

std::vector<std::string>& CustomerDash::getMatured() 
{ 
    return maturedIds; 
}

    
void CustomerDash::clear() 
{
     maturedIds.clear(); 
}