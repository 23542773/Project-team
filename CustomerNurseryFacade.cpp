#include "CustomerNurseryFacade.h"

// TEMPORARY: Include dummy subsystems for testing
// When real classes ready, replace these includes with real class headers
#include "dummy/DummySpeciesCatalog.h"
#include "dummy/DummyPlantKitFactory.h"
#include "dummy/DummyPackageDirector.h"
#include "dummy/DummyInventoryService.h"
#include "dummy/DummySalesService.h"
#include "dummy/DummyOrderItem.h"
#include "dummy/DummyPlantFlyweight.h"
#include "dummy/DummyPlant.h"
#include "dummy/DummyPlantState.h"

#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <iostream>

/**
 * @file CustomerNurseryFacade.cpp
 * @brief Implementation of customer-facing facade
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 */

/**
 * @brief Constructor
 * @param catalog Pointer to SpeciesCatalog
 * @param factory Pointer to PlantKitFactory
 * @param director Pointer to PackageDirector
 * @param inv Pointer to InventoryService
 * @param sales Pointer to SalesService
 */
CustomerNurseryFacade::CustomerNurseryFacade(SpeciesCatalog* catalog, PlantKitFactory* factory, PackageDirector* director, InventoryService* inv, SalesService* sales)
    : NurseryFacade(catalog, inv, sales), factory(factory), director(director) 
{
    if (!factory) 
    {
        throw std::invalid_argument("CustomerNurseryFacade: PlantKitFactory pointer cannot be null");
    }
    
    if (!director) 
    {
        throw std::invalid_argument("CustomerNurseryFacade: PackageDirector pointer cannot be null");
    }
    
    std::cout << "[CustomerNurseryFacade] Initialized successfully\n";
}

/**
 * @brief Destructor
 */
CustomerNurseryFacade::~CustomerNurseryFacade() 
{
    factory = nullptr;
    director = nullptr;
    
    std::cout << "[CustomerNurseryFacade] Destroyed\n";
}

/**
 * @brief Browse available plant species by SKUs
 * @param skus Vector of SKU strings to check
 * @return Vector of available plant descriptions
 */
std::vector<std::string> CustomerNurseryFacade::browseAvailable(const std::vector<std::string>& skus) 
{
    std::cout << "\n[CustomerNurseryFacade::browseAvailable] Browsing " << skus.size() << " SKUs...\n";
    
    std::vector<std::string> available;
    
    // Cast to dummy types for now (when real types come, remove casts)
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        std::cerr << "[CustomerNurseryFacade::browseAvailable] ERROR: Invalid subsystems\n";
        return available;
    }
    
    // Iterate through requested SKUs
    for (const auto& sku : skus) 
    {
        try 
        {
            // DELEGATION 1: Query InventoryService for stock level
            int stock = dummyInv->available(sku);
            
            // Only include items with stock > 0
            if (stock > 0) 
            {
                // DELEGATION 2: Get species information from catalog
                DummyPlantFlyweight* species = dummyCatalog->getBySKU(sku);
                
                if (species) 
                {
                    // Format the plant information
                    std::ostringstream details;
                    details << sku << " (" << species->speciesName() << "): " << stock << " in stock";
                    
                    // Add stock level indicators
                    if (stock < 5) 
                    {
                        details << " (LOW STOCK!)";
                    } 
                    else if (stock > 20) 
                    {
                        details << " (Well stocked)";
                    }
                    
                    // Add to result vector
                    available.push_back(details.str());
                    std::cout << "  ✓ " << details.str() << "\n";
                }
                else 
                {
                    std::cout << "  ✗ " << sku << ": Species not found in catalog\n";
                }
            } 
            else 
            {
                std::cout << "  ✗ " << sku << ": Out of stock\n";
            }
        } 
        catch (const std::exception& e) 
        {
            // Handle invalid SKUs gracefully - skip them
            std::cerr << "  ✗ " << sku << ": Error - " << e.what() << "\n";
            continue;
        }
    }
    
    std::cout << "[CustomerNurseryFacade::browseAvailable] Found " << available.size() << " available plants\n";
    
    return available;
}

/**
 * @brief Get detailed information about a specific plant species
 * @param sku SKU identifier
 * @return Formatted string with plant details
 */
std::string CustomerNurseryFacade::getPlantDetails(const std::string& sku)
{
    std::cout << "\n[CustomerNurseryFacade::getPlantDetails] Getting details for " << sku << "...\n";
    
    std::ostringstream details;
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        throw std::runtime_error("Invalid subsystems");
    }
    
    try 
    {
        // DELEGATION 1: Get stock level from InventoryService
        int stock = dummyInv->available(sku);
        
        // DELEGATION 2: Get species information from catalog
        DummyPlantFlyweight* species = dummyCatalog->getBySKU(sku);
        
        if (!species) 
        {
            throw std::invalid_argument("Invalid SKU: " + sku);
        }
        
        // Get care requirements
        DummyCarePresets care = species->careDefaults();
        
        // Format comprehensive output
        details << "========== PLANT DETAILS ==========\n";
        details << "SKU: " << sku << "\n";
        details << "Common Name: " << species->speciesName() << "\n";
        details << "Environment: " << species->envType() << "\n";
        details << "Stock Level: " << stock;
        
        // Add stock status indicators
        if (stock == 0) 
        {
            details << " (OUT OF STOCK)";
        } 
        else if (stock < 5) 
        {
            details << " (LOW STOCK - ORDER SOON!)";
        } 
        else if (stock > 20) 
        {
            details << " (Well stocked)";
        }
        details << "\n\n";
        
        // Care requirements section
        details << "Care Requirements:\n";
        details << "  Water: " << care.baseWaterInMl << "ml per watering\n";
        details << "  Light: " << care.idealLightInHours << " hours per day\n";
        details << "  Fertilize: Every " << care.fertilizeFreqInDays << " days\n";
        details << "===================================\n";
        
        std::cout << "[CustomerNurseryFacade::getPlantDetails] Details retrieved successfully\n";
        
        return details.str();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "[CustomerNurseryFacade::getPlantDetails] ERROR: " << e.what() << "\n";
        throw std::invalid_argument("Invalid SKU: " + sku);
    }
}

/**
 * @brief Build a default custom plant package
 * @param f Pointer to PlantKitFactory
 * @param id Identifier for the package
 * @return Pointer to constructed CustomPlantPackage
 */
CustomPlantPackage* CustomerNurseryFacade::buildDefaultPackage(PlantKitFactory* f, const std::string& id)
{
    std::cout << "\n[CustomerNurseryFacade::buildDefaultPackage] Building package for " << id << "...\n";
    
    // Validate factory parameter
    if (!f) 
    {
        throw std::invalid_argument("Factory cannot be null");
    }
    
    // DELEGATION: Let director coordinate the Builder pattern
    // This hides Builder pattern complexity from customer
    DummyPackageDirector* dummyDirector = dynamic_cast<DummyPackageDirector*>(director);
    
    if (dummyDirector) 
    {
        dummyDirector->construct();
    }
    
    // TODO: Get the completed package from builder through director
    // For now, return nullptr since builder isn't fully implemented
    // When real builder is ready:
    // CustomPlantPackage* package = director->getResult();
    // if (!package) 
    // {
    //     throw std::runtime_error("Failed to build package");
    // }
    // return package;
    
    std::cout << "[CustomerNurseryFacade::buildDefaultPackage] Package construction delegated to director\n";
    
    return nullptr;  // PLACEHOLDER - will return real package when builder ready
}

/**
 * @brief Generate order receipt for a customer
 * @param custId Customer identifier
 * @param items Vector of OrderItem pointers
 * @return Formatted receipt string
 */
std::string CustomerNurseryFacade::orderReceipt(const std::string& custId, const std::vector<OrderItem*>& items)
{
    std::cout << "\n[CustomerNurseryFacade::orderReceipt] Generating receipt for " << custId << "...\n";
    
    std::ostringstream receipt;
    
    // Format receipt header with title
    receipt << "========================================\n";
    receipt << "      PLANT NURSERY - ORDER RECEIPT      \n";
    receipt << "========================================\n\n";
    
    // Add customer information
    receipt << "Customer ID: " << custId << "\n";
    receipt << "Date: 2025-10-27\n";
    receipt << "----------------------------------------\n\n";
    
    // Items header
    receipt << "ITEMS:\n";
    
    // Calculate totals
    double subtotal = 0.0;
    
    // Format each item
    for (const auto& item : items) 
    {
        // Cast to DummyOrderItem for now
        DummyOrderItem* dummyItem = dynamic_cast<DummyOrderItem*>(item);
        
        if (dummyItem) 
        {
            // Left-aligned item ID, right-aligned price
            receipt << std::left << std::setw(30) << dummyItem->id;
            receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << dummyItem->price << "\n";
            
            subtotal += dummyItem->price;
        }
    }
    
    // Calculate VAT (15% South African standard)
    double tax = subtotal * 0.15;
    double total = subtotal + tax;
    
    // Totals section
    receipt << "\n----------------------------------------\n";
    
    receipt << std::left << std::setw(30) << "Subtotal:";
    receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << subtotal << "\n";
    
    receipt << std::left << std::setw(30) << "VAT (15%):";
    receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << tax << "\n";
    
    receipt << std::left << std::setw(30) << "TOTAL:";
    receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << total << "\n";

    // Footer with thank you message
    receipt << "========================================\n";
    receipt << "     Thank you for your purchase!       \n";
    receipt << "========================================\n";
    
    std::cout << "[CustomerNurseryFacade::orderReceipt] Receipt generated successfully\n";
    
    return receipt.str();
}

/**
 * @brief Place an order for a customer (SHOWCASE METHOD)
 * @param custId Customer identifier
 * @param items Vector of OrderItem pointers
 */
void CustomerNurseryFacade::placeOrder(const std::string& custId, const std::vector<OrderItem*>& items)
{
    std::cout << "\n[CustomerNurseryFacade::placeOrder] *** SHOWCASE METHOD ***\n";
    std::cout << "Processing order for customer: " << custId << "\n";
    std::cout << "Items in order: " << items.size() << "\n";
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySalesService* dummySales = dynamic_cast<DummySalesService*>(sales);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummySales || !dummyCatalog) 
    {
        throw std::runtime_error("Invalid subsystems");
    }
    
    // ========================================================================
    // STEP 1: VALIDATION
    // ========================================================================
    std::cout << "\n--- STEP 1: VALIDATION ---\n";
    
    // Validate inventory BEFORE making any changes
    for (const auto& item : items) 
    {
        DummyOrderItem* dummyItem = dynamic_cast<DummyOrderItem*>(item);
        
        if (!dummyItem) 
        {
            throw std::runtime_error("Invalid order item");
        }
        
        // Check stock level
        int stock = dummyInv->available(dummyItem->id);
        std::cout << "  Checking " << dummyItem->id << ": stock=" << stock << "\n";
        
        if (stock <= 0) 
        {
            throw std::runtime_error("Insufficient stock for item: " + dummyItem->id);
        }
        
        // Validate SKU exists in catalog
        if (!dummyCatalog->hasSKU(dummyItem->id)) 
        {
            throw std::invalid_argument("Invalid SKU: " + dummyItem->id);
        }
        
        // Check if plant is in sellable state
        DummyPlant* plant = dummyInv->getPlant(dummyItem->id);
        if (plant) 
        {
            if (!plant->canBeSold()) 
            {
                throw std::runtime_error("Plant not ready for sale: " + dummyItem->id + " (state: " + plant->getState()->getStateName() + ")");
            }
        }
    }
    
    // Verify customer exists
    if (!dummySales->customerExists(custId)) 
    {
        throw std::invalid_argument("Invalid customer ID: " + custId);
    }
    
    std::cout << "  ✓ All validations passed\n";
    
    // ========================================================================
    // STEP 2: CREATE ORDER
    // ========================================================================
    std::cout << "\n--- STEP 2: CREATE ORDER ---\n";
    
    // DELEGATION: SalesService handles order creation
    std::vector<DummyOrderItem*> dummyItems;
    for (auto item : items) 
    {
        dummyItems.push_back(dynamic_cast<DummyOrderItem*>(item));
    }
    
    std::string orderId = dummySales->createOrder(custId, dummyItems);
    std::cout << "  ✓ Order created: " << orderId << "\n";
    
    // Order now exists with status "PENDING"
    // SalesService will automatically notify observers (Observer pattern)
    
    // ========================================================================
    // STEP 3: UPDATE INVENTORY
    // ========================================================================
    std::cout << "\n--- STEP 3: UPDATE INVENTORY ---\n";
    
    // DELEGATION: InventoryService consumes stock
    for (const auto& item : items) 
    {
        DummyOrderItem* dummyItem = dynamic_cast<DummyOrderItem*>(item);
        
        if (dummyItem) 
        {
            bool success = dummyInv->consume(dummyItem->id, dummyItem->quantity);
            
            if (!success) 
            {
                // Transaction failed mid-way
                // In production: implement rollback mechanism
                throw std::runtime_error("Failed to consume inventory for: " + dummyItem->id);
            }
            
            std::cout << "  ✓ Consumed " << dummyItem->quantity << " unit(s) of " << dummyItem->id << "\n";
        }
    }
    
    // ========================================================================
    // STEP 4: AUTOMATIC NOTIFICATIONS (Observer pattern)
    // ========================================================================
    std::cout << "\n--- STEP 4: AUTOMATIC NOTIFICATIONS ---\n";
    std::cout << "  ℹ SalesService notifies observers with OrderEvent\n";
    std::cout << "  ℹ InventoryService notifies observers with StockEvent\n";
    std::cout << "  ℹ NurseryHub receives notifications (Mediator pattern)\n";
    std::cout << "  ℹ StaffDashboard updated automatically\n";
    std::cout << "  ℹ Staff assigned via StaffService coordination\n";
    
    // These happen AUTOMATICALLY through the Observer pattern
    // No explicit notification needed - the beauty of combining patterns!
    
    std::cout << "\n[CustomerNurseryFacade::placeOrder] ✓ Order completed successfully!\n";
    std::cout << "  Order ID: " << orderId << "\n";
    std::cout << "  Items processed: " << items.size() << "\n";
    std::cout << "  Status: PENDING\n";
}

/**
 * @brief Validate facade is properly configured
 * @return true if all subsystems are valid
 */
bool CustomerNurseryFacade::isValid() const
{
    // Check shared subsystems (inherited from base)
    if (!areSharedSubsystemsValid()) 
    {
        return false;
    }
    
    // Check customer-specific subsystems
    if (!factory) 
    {
        return false;
    }
    
    if (!director) 
    {
        return false;
    }
    
    // All subsystems valid
    return true;
}