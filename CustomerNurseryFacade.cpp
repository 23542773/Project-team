#include "CustomerNurseryFacade.h"

//connections we need to make
// #include "SpeciesCatalog.h"
// #include "PlantKitFactory.h"
// #include "PackageDirector.h"
// #include "InventoryService.h"
// #include "SalesService.h"
// #include "CustomPlantPackage.h"
// #include "OrderItem.h"

CustomerNurseryFacade::CustomerNurseryFacade(SpeciesCatalog* catalog, PlantKitFactory* factory, PackageDirector* director, InventoryService* inv, SalesService* sales)
    : NurseryFacade(catalog, inv, sales),factory(factory),director(director) 
{

}

CustomerNurseryFacade::~CustomerNurseryFacade() 
{

}

std::vector<std::string> CustomerNurseryFacade::browseAvailable(const std::vector<std::string>& skus) 
{
    std::vector<std::string> available;
    return available;
}

std::string CustomerNurseryFacade::getPlantDetails(const std::string& sku)
{
    
}

CustomPlantPackage* CustomerNurseryFacade::buildDefaultPackage( PlantKitFactory* f, const std::string& id)
{

}

std::string CustomerNurseryFacade::orderReceipt(const std::string& custId, const std::vector<OrderItem*>& items)
{

}

void CustomerNurseryFacade::placeOrder(const std::string& custId, const std::vector<OrderItem*>& items)
{

}

// bool CustomerNurseryFacade::isAvailableForPurchase(const std::string& sku)
// {

// }

bool CustomerNurseryFacade::isValid() const
{

}