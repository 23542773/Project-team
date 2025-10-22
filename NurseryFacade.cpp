#include "NurseryFacade.h"
//classes we need connections with
//#include "SpeciesCatalog.h"
//#include "InventoryService.h"
//#include "SalesService.h"

NurseryFacade::NurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales)
    :catalog(catalog),inv(inv),sales(sales) 
      {
        //implementation like validation checks
      }

//bool NurseryFacade::areSharedSubsystemsValid() const 
// {
    // Check if all shared subsystems are non-null so we can actually use them
// }  

