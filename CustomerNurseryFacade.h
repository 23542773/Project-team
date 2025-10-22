#ifndef CUSTOMERNURSERYFACADE_H
#define CUSTOMERNURSERYFACADE_H

#include "NurseryFacade.h"
#include <string>
#include <vector>

class PlantKitFactory;
class PackageDirector;
class CustomPlantPackage;
class OrderItem;

class CustomerNurseryFacade : public NurseryFacade
{
    private:
    PlantKitFactory* factory;
    PackageDirector* director;

    public:
    CustomerNurseryFacade(SpeciesCatalog* catalog, PlantKitFactory* factory, PackageDirector* director, InventoryService* inv, SalesService* sales);
    ~CustomerNurseryFacade();
    std::vector<std::string> browseAvailable(const std::vector<std::string>& skus);
    std::string getPlantDetails(const std::string& sku);
    CustomPlantPackage* buildDefaultPackage(PlantKitFactory* f, const std::string& id);
    std::string orderReceipt(const std::string& custId, const std::vector<OrderItem*>& items);
    void placeOrder(const std::string& custId, const std::vector<OrderItem*>& items);
    //potential stock management check spot
    //bool isAvailableForPurchase(const std::string& sku);
    bool isValid() const override;

};
#endif;