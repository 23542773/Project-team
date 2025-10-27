#include "NurseryFacade.h"

#include "DummySpeciesCatalog.h"
#include "DummyInventoryService.h"
#include "DummySalesService.h"

#include <stdexcept>

/**
 * @file NurseryFacade.cpp
 * @brief Implementation of abstract base facade
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 */

/**
 * @brief Protected constructor
 * @param catalog Pointer to SpeciesCatalog
 * @param inv Pointer to InventoryService
 * @param sales Pointer to SalesService
 */
NurseryFacade::NurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales)
    : catalog(catalog), inv(inv), sales(sales) 
{
    // Validate all shared subsystems are provided (defensive programming)
    if (!catalog) 
    {
        throw std::invalid_argument("NurseryFacade: SpeciesCatalog pointer cannot be null");
    }
    
    if (!inv) 
    {
        throw std::invalid_argument("NurseryFacade: InventoryService pointer cannot be null");
    }
    
    if (!sales) 
    {
        throw std::invalid_argument("NurseryFacade: SalesService pointer cannot be null");
    }
    
    // All subsystems validated - facade is ready
}

/**
 * @brief Check if all shared subsystems are valid
 * @return true if all shared subsystems are non-null
 */
bool NurseryFacade::areSharedSubsystemsValid() const 
{
    // Check if all shared subsystems are non-null
    return catalog != nullptr && inv != nullptr && sales != nullptr;
}