#ifndef CUSTOMERNURSERYFACADE_H
#define CUSTOMERNURSERYFACADE_H

#include "NurseryFacade.h"
#include <string>
#include <vector>

class PlantKitFactory;
class PackageDirector;
class CustomPlantPackage;
class OrderItem;

/**
 * @file CustomerNurseryFacade.h
 * @brief Customer-facing facade for Plant Nursery operations
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 */

class CustomerNurseryFacade : public NurseryFacade
{
    private:
    PlantKitFactory* factory;
    PackageDirector* director;

    public:
    
    /**
     * @brief Constructor
     */
    CustomerNurseryFacade(SpeciesCatalog* catalog, PlantKitFactory* factory, PackageDirector* director, InventoryService* inv, SalesService* sales);

    /**
     * @brief Destructor
     */
    ~CustomerNurseryFacade();
    
    /**
     * @brief Browse available plant species by SKUs
     */
    std::vector<std::string> browseAvailable(const std::vector<std::string>& skus);
    
    /**
     * @brief Get detailed information about a specific plant species
     */
    std::string getPlantDetails(const std::string& sku);

    /**
     * @brief Build a default custom plant package
     */
    CustomPlantPackage* buildDefaultPackage(PlantKitFactory* f, const std::string& id);

    /**
     * @brief Generate order receipt for a customer
     */
    std::string orderReceipt(const std::string& custId, const std::vector<OrderItem*>& items);

    /**
     * @brief Place an order for a customer
     */
    void placeOrder(const std::string& custId, const std::vector<OrderItem*>& items);

    //potential stock management check spot
    //bool isAvailableForPurchase(const std::string& sku);
    /**
     * @brief Validate facade is properly configured
     * @return true if all subsystems are valid
     */
    bool isValid() const override;

};
#endif //CUSTOMERNURSERYFACADE_H