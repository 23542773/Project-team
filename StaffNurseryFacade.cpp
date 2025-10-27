#include "StaffNurseryFacade.h"

// TEMPORARY: Include dummy subsystems for testing
// When real classes ready, replace these includes with real class headers
#include "DummySpeciesCatalog.h"
#include "DummyInventoryService.h"
#include "DummySalesService.h"
#include "DummyPlant.h"
#include "DummyPlantState.h"
#include "DummyPlantFlyweight.h"

#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <algorithm>

/**
 * @file StaffNurseryFacade.cpp
 * @brief Implementation of staff-facing facade
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 */

/**
 * @brief Constructor
 * @param catalog Pointer to SpeciesCatalog
 * @param inv Pointer to InventoryService
 * @param sales Pointer to SalesService
 */
StaffNurseryFacade::StaffNurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales)
    : NurseryFacade(catalog, inv, sales) 
{
    // Staff facade only needs shared subsystems
    // Base class already validated them
    
    std::cout << "[StaffNurseryFacade] Initialized successfully\n";
}

/**
 * @brief Destructor
 */
StaffNurseryFacade::~StaffNurseryFacade() 
{
    // Facade does NOT own subsystems
    // Base class will handle cleanup
    
    std::cout << "[StaffNurseryFacade] Destroyed\n";
}

/**
 * @brief Restock inventory with new plants from supplier
 * @param sku SKU identifier to restock
 * @param qty Quantity to add to inventory
 */
void StaffNurseryFacade::restock(const std::string& sku, int qty) 
{
    std::cout << "\n[StaffNurseryFacade::restock] Restocking " << sku << " with " << qty << " units...\n";
    
    // Validate quantity is positive
    if (qty <= 0) 
    {
        throw std::invalid_argument("Restock quantity must be positive");
    }
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        throw std::runtime_error("Invalid subsystems");
    }
    
    // Validate SKU exists in catalog
    if (!dummyCatalog->hasSKU(sku)) 
    {
        throw std::invalid_argument("Invalid SKU: " + sku);
    }
    
    // DELEGATION: Delegate to inventory service
    // This will automatically trigger Observer notifications
    dummyInv->restock(sku, qty);
    
    std::cout << "[StaffNurseryFacade::restock] ✓ Restocking complete\n";
    std::cout << "  ℹ StaffDashboard will be notified automatically (Observer pattern)\n";
    std::cout << "  ℹ Low stock alerts cleared if applicable\n";
}

/**
 * @brief Get list of plants ready for sale (in MATURE state)
 * @return Vector of SKUs for plants ready to sell
 */
std::vector<std::string> StaffNurseryFacade::getReadyForSale() 
{
    std::cout << "\n[StaffNurseryFacade::getReadyForSale] Finding sellable plants...\n";
    
    std::vector<std::string> ready;
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    
    if (!dummyInv) 
    {
        std::cerr << "[StaffNurseryFacade::getReadyForSale] ERROR: Invalid inventory service\n";
        return ready;
    }
    
    // Query all plants from inventory
    std::vector<DummyPlant*> allPlants = dummyInv->getAllPlants();
    
    std::cout << "  Checking " << allPlants.size() << " plants...\n";
    
    // Filter for sellable plants
    for (const auto& plant : allPlants) 
    {
        if (!plant) 
        {
            continue;
        }
        
        // Check if in stock
        int stock = dummyInv->available(plant->getId());
        
        if (stock > 0) 
        {
            // Check if in MATURE state (can be sold)
            if (plant->getState() && plant->getState()->canSell()) 
            {
                ready.push_back(plant->getId());
                
                std::cout << "  ✓ " << plant->getId() << " (state: " << plant->getState()->getStateName() << ", stock: " << stock << ")\n";
            } 
            else 
            {
                std::cout << "  ✗ " << plant->getId() << " (state: " << plant->getState()->getStateName() << " - not ready)\n";
            }
        }
    }
    
    std::cout << "[StaffNurseryFacade::getReadyForSale] Found " << ready.size() << " plants ready for sale\n";
    
    return ready;
}

/**
 * @brief Check if specific plant is available for purchase
 * @param sku SKU to check
 * @return true if in stock AND in sellable state
 */
bool StaffNurseryFacade::isAvailableForPurchase(const std::string& sku) 
{
    std::cout << "\n[StaffNurseryFacade::isAvailableForPurchase] Checking " << sku << "...\n";
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    
    if (!dummyInv) 
    {
        return false;
    }
    
    try 
    {
        // Check stock level
        int stock = dummyInv->available(sku);
        std::cout << "  Stock: " << stock << "\n";
        
        if (stock <= 0) 
        {
            std::cout << "  ✗ Out of stock\n";
            return false;
        }
        
        // Check plant state
        DummyPlant* plant = dummyInv->getPlant(sku);
        
        if (!plant) 
        {
            std::cout << "  ✗ Plant not found\n";
            return false;
        }
        
        bool canSell = plant->getState()->canSell();
        std::cout << "  State: " << plant->getState()->getStateName() << " (canSell: " << (canSell ? "YES" : "NO") << ")\n";
        
        if (canSell) 
        {
            std::cout << "  ✓ Available for purchase\n";
            return true;
        } 
        else 
        {
            std::cout << "  ✗ Not in sellable state\n";
            return false;
        }
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "  ✗ Error: " << e.what() << "\n";
        return false;
    }
}

/**
 * @brief Validate stock availability and return detailed status
 * @param sku SKU to validate
 * @param requiredQty Quantity needed
 * @return Status string (AVAILABLE, PARTIAL, UNAVAILABLE, INVALID_SKU)
 */
std::string StaffNurseryFacade::validateStock(const std::string& sku, int requiredQty) 
{
    std::cout << "\n[StaffNurseryFacade::validateStock] Validating " << sku << " (need " << requiredQty << ")...\n";
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        return "ERROR";
    }
    
    // Check if SKU exists
    if (!dummyCatalog->hasSKU(sku)) 
    {
        std::cout << "  ✗ Invalid SKU\n";
        return "INVALID_SKU";
    }
    
    // Get current stock
    int currentStock = dummyInv->available(sku);
    std::cout << "  Current stock: " << currentStock << "\n";
    
    // Compare with required quantity
    if (currentStock >= requiredQty) 
    {
        std::cout << "  ✓ Sufficient stock available\n";
        return "AVAILABLE";
    } 
    else if (currentStock > 0) 
    {
        std::cout << "  ⚠ Partial stock available (" << currentStock << "/" << requiredQty << ")\n";
        return "PARTIAL";
    } 
    else 
    {
        std::cout << "  ✗ Out of stock\n";
        return "UNAVAILABLE";
    }
}

/**
 * @brief Get comprehensive inventory summary for staff dashboard
 * @return Formatted summary string
 */
std::string StaffNurseryFacade::getInventorySummary() 
{
    std::cout << "\n[StaffNurseryFacade::getInventorySummary] Generating summary...\n";
    
    std::ostringstream summary;
    
    // Cast to dummy types
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    
    if (!dummyInv) 
    {
        return "ERROR: Invalid inventory service";
    }
    
    // Query all inventory data
    std::vector<DummyPlant*> allPlants = dummyInv->getAllPlants();
    std::vector<std::string> allSKUs = dummyInv->getAllSKUs();
    
    int totalSKUs = allSKUs.size();
    int readyForSale = 0;
    int lowStock = 0;
    int outOfStock = 0;
    
    std::vector<std::pair<std::string, int>> lowStockItems;
    std::vector<std::string> outOfStockItems;
    
    // Count items by status
    for (const auto& sku : allSKUs) 
    {
        int stock = dummyInv->available(sku);
        DummyPlant* plant = dummyInv->getPlant(sku);
        
        if (stock == 0) 
        {
            outOfStock++;
            outOfStockItems.push_back(sku);
        } 
        else if (stock < 5) 
        {
            lowStock++;
            lowStockItems.push_back({sku, stock});
        } 
        else if (plant && plant->getState() && plant->getState()->canSell()) 
        {
            readyForSale++;
        }
    }
    
    // Format summary
    summary << "===== INVENTORY SUMMARY =====\n";
    summary << "Total SKUs: " << totalSKUs << "\n";
    summary << "Ready for Sale: " << readyForSale << "\n";
    summary << "Low Stock (<5): " << lowStock << "\n";
    summary << "Out of Stock: " << outOfStock << "\n";
    
    // List low stock items
    if (!lowStockItems.empty()) 
    {
        summary << "\nLOW STOCK ALERTS:\n";
        for (const auto& item : lowStockItems) 
        {
            summary << "  - " << item.first << ": " << item.second << " remaining\n";
        }
    }
    
    // List out of stock items
    if (!outOfStockItems.empty()) 
    {
        summary << "\nOUT OF STOCK:\n";
        for (const auto& sku : outOfStockItems) 
        {
            summary << "  - " << sku << "\n";
        }
    }
    
    summary << "=============================\n";
    
    std::cout << "[StaffNurseryFacade::getInventorySummary] Summary generated\n";
    
    return summary.str();
}

/**
 * @brief Validate facade is properly configured
 * @return true if all subsystems are valid
 */
bool StaffNurseryFacade::isValid() const 
{
    // Check shared subsystems only (staff facade is simpler!)
    // No additional subsystems to check
    return areSharedSubsystemsValid();
}