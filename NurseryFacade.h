#ifndef NURSERYFACADE_H
#define NURSERYFACADE_H

#include <string>
#include <vector>

// Forward declarations - will be replaced with real classes when team finishes
class SpeciesCatalog;
class InventoryService;
class SalesService;
class PlantKitFactory;
class PackageDirector;
class CustomPlantPackage;
class OrderItem;

/**
 * @file NurseryFacade.h
 * @brief Abstract base facade for Plant Nursery Simulator
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 * 
 *  * Single facade providing both customer and staff operations.
 * GUI layer controls which operations are visible to which user type.
 * 
 * TEMPORARY IMPLEMENTATION:
 * Currently uses dummy subsystem types. When real pattern implementations
 * are ready, simply swap the dummy includes for real class includes.
 */

// Single Conversion of facade
class NurseryFacade
{
    private:
        // Subsystem pointers (shared by all operations)
        SpeciesCatalog* catalog;
        InventoryService* inv;
        SalesService* sales;
        PlantKitFactory* factory;
        PackageDirector* director;
        
     public:
        /**
         * @brief Constructor
         * @param catalog Pointer to SpeciesCatalog (Flyweight pattern)
         * @param factory Pointer to PlantKitFactory (Factory pattern)
         * @param director Pointer to PackageDirector (Builder pattern)
         * @param inv Pointer to InventoryService (manages Plant inventory)
         * @param sales Pointer to SalesService (manages orders)
         */
        NurseryFacade(SpeciesCatalog* catalog, PlantKitFactory* factory, PackageDirector* director, InventoryService* inv, SalesService* sales);
   
        /*
        * @brief destructor
        */
        ~NurseryFacade();

        /**
         * @brief Browse available plants by SKUs
         * @param skus Vector of SKU strings to check
         * @return Vector of SKUs that are available
         */
        std::vector<std::string> browseAvailable(const std::vector<std::string>& skus);

        /**
         * @brief Get detailed information about a plant SKU
         * @param sku SKU identifier
         * @return Formatted string with plant details
         */
        std::string getPlantDetails(const std::string& sku);

        /**
         * @brief Build a default plant package for a given SKU
         * @param f Pointer to PlantKitFactory
         * @param id SKU identifier
         * @return Pointer to constructed CustomPlantPackage
         */
        CustomPlantPackage* buildDefaultPackage(PlantKitFactory* f, const std::string& id);

        /**
         * @brief Generate receipt for customer order
         * @param custId Customer ID
         * @param items Vector of OrderItems
         * @return Formatted receipt string
         */
        std::string generateReceipt(const std::string& custId, const std::vector<OrderItem*>& items);

        /**
         * @brief Place an order for a customer
         * @param custId Customer ID
         * @param items Vector of OrderItems
         */
        void placeOrder(const std::string& custId, const std::vector<OrderItem*>& items);

        /**
         * @brief Restock inventory with new plants from supplier
         * @param sku SKU identifier to restock
         * @param qty Quantity to add to inventory
         */
        void restock(const std::string& sku, int qty);
        
        /**
         * @brief Get list of plants ready for sale (in MATURE state)
         * @return Vector of SKUs for plants ready to sell
         */
        std::vector<std::string> getReadyForSale();
        
        /**
         * @brief Check if specific plant is available for purchase
         * @param sku SKU to check
         * @return true if in stock AND in sellable state
         */
        bool isAvailableForPurchase(const std::string& sku);
        
        /**
         * @brief Validate stock availability and return detailed status
         * @param sku SKU to validate
         * @param requiredQty Quantity needed
         * @return Status string (AVAILABLE, PARTIAL, UNAVAILABLE, INVALID_SKU)
         */
        std::string validateStock(const std::string& sku, int requiredQty);
        
        /**
         * @brief Get comprehensive inventory summary for staff dashboard
         * @return Formatted summary string
         */
        std::string getInventorySummary();

        /**
         * @brief Validate facade is properly configured
         * @return true if all subsystems are valid
         */
        bool isValid() const;
        
        /**
         * @brief Get all available SKUs in catalog
         * @return Vector of SKU strings
         */
        std::vector<std::string> getAllSKUs() const;

    private:
        /**
         * @brief Check if all subsystems are valid
         * @return true if all pointers are non-null
         */
        bool areSubsystemsValid() const;
        
        // Prevent copying and moving
        NurseryFacade(const NurseryFacade&) = delete;
        NurseryFacade& operator=(const NurseryFacade&) = delete;
        NurseryFacade(NurseryFacade&&) = delete;
        NurseryFacade& operator=(NurseryFacade&&) = delete;
};

#endif // NURSERYFACADE_H