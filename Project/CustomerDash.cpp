/**
 * @file CustomerDash.cpp
 * @brief Implementation of CustomerDash Observer methods
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * Implementation of CustomerDash Observer methods
 */
#include "CustomerDash.h"

/**
 * @brief Handle Plant lifecycle events
 * @param e The Plant event data ID, SKU and event type
 * @returns void
 */
void CustomerDash::onEvent(events::Plant e)  
{
    if (e.type == events::PlantType::Matured) maturedIds.push_back(e.plantId);
}

/**
 * @brief Get the list of matured plant IDs for the customer dashboard
 * @returns A vector of matured plant IDs
 */
std::vector<std::string>& CustomerDash::getMatured() 
{ 
    return maturedIds; 
}

/**
 * @brief Clear the list of matured plant IDs
 * @returns void
 */
void CustomerDash::clear() 
{
     maturedIds.clear(); 
}
