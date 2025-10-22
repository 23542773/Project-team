#include "StaffNurseryFacade.h"

//connections
// #include "SpeciesCatalog.h"
// #include "InventoryService.h"
// #include "SalesService.h"

StaffNurseryFacade::StaffNurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales)
    : NurseryFacade(catalog, inv, sales) 
{
}

StaffNurseryFacade::~StaffNurseryFacade() 
{

}

void StaffNurseryFacade::restock(const std::string& sku, int qty) 
{

}

std::vector<std::string> StaffNurseryFacade::getReadyForSale() 
{

}

bool StaffNurseryFacade::isAvailableForPurchase(const std::string& sku) 
{
   
}

std::string StaffNurseryFacade::validateStock(const std::string& sku, int requiredQty) 
{
    
}

std::string StaffNurseryFacade::getInventorySummary() 
{
    
}

// std::vector<std::string> StaffNurseryFacade::getLowStockAlert() 
// {
    
// }

// std::vector<std::string> StaffNurseryFacade::getOutOfStockItems() 
// {
    
// }

bool StaffNurseryFacade::isValid() const 
{
   
}