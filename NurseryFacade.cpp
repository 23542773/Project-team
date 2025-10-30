#include "NurseryFacade.h"

#include "DummySpeciesCatalog.h"
#include "DummyInventoryService.h"
#include "DummySalesService.h"
#include "DummyPlantKitFactory.h"
#include "DummyPackageDirector.h"
#include "DummyOrderItem.h"
#include "DummyPlant.h"
#include "DummyPlantState.h"
#include "DummyPlantFlyweight.h"

#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <algorithm>

/**
 * @file NurseryFacade.cpp
 * @brief Implementation of unified facade
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-30
 */

//combined the staff and customer facades to make sure we could integrate with the gui which already protects users from staff vs customer oprations(making double facade pointless overkill)

/**
 * @brief Constructor
 * @param catalog Pointer to SpeciesCatalog (Flyweight pattern)
 * @param factory Pointer to PlantKitFactory (Factory pattern)
 * @param director Pointer to PackageDirector (Builder pattern)
 * @param inv Pointer to InventoryService (manages Plant inventory)
 * @param sales Pointer to SalesService (manages orders)
 */
NurseryFacade::NurseryFacade(SpeciesCatalog* catalog,PlantKitFactory* factory,PackageDirector* director,InventoryService* inv,SalesService* sales)
    : catalog(catalog), inv(inv), sales(sales), factory(factory), director(director)
{
    // Validate all subsystems are provided
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
    
    if (!factory) 
    {
        throw std::invalid_argument("NurseryFacade: PlantKitFactory pointer cannot be null");
    }
    
    if (!director) 
    {
        throw std::invalid_argument("NurseryFacade: PackageDirector pointer cannot be null");
    }
    
    std::cout << "[NurseryFacade] Initialized successfully (unified facade)\n";
}

/**
 * @brief Destructor
 */
NurseryFacade::~NurseryFacade() 
{
    //we dont own the subsystems so we dont need to delete the subsystems
    catalog = nullptr;
    inv = nullptr;
    sales = nullptr;
    factory = nullptr;
    director = nullptr;
    
    std::cout << "[NurseryFacade] Destroyed\n";
}

//Customer section

/**
 * @brief Browse available plants by SKUs
 * @param skus Vector of SKU strings to check
 * @return Vector of SKUs that are available
 */
std::vector<std::string> NurseryFacade::browseAvailable(const std::vector<std::string>& skus) 
{
    std::cout << "\n[NurseryFacade::browseAvailable] Browsing " << skus.size() << " SKUs...\n";
    
    std::vector<std::string> available;
    
    // Cast to dummy types for now (when real types come, remove casts)
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        std::cerr << "[NurseryFacade::browseAvailable] ERROR: Invalid subsystems\n";
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
            std::cerr << "  ✗ " << sku << ": Error - " << e.what() << "\n";
            continue;
        }
    }
    
    std::cout << "[NurseryFacade::browseAvailable] Found " << available.size() << " available plants\n";
    
    return available;
}

/**
 * @brief Get detailed information about a plant SKU
 * @param sku SKU identifier
 * @return Formatted string with plant details
 */
std::string NurseryFacade::getPlantDetails(const std::string& sku)
{
    std::cout << "\n[NurseryFacade::getPlantDetails] Getting details for " << sku << "...\n";
    
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
        
        details << "Care Requirements:\n";
        details << "  Water: " << care.baseWaterInMl << "ml per watering\n";
        details << "  Light: " << care.idealLightInHours << " hours per day\n";
        details << "  Fertilize: Every " << care.fertilizeFreqInDays << " days\n";
        details << "===================================\n";
        
        std::cout << "[NurseryFacade::getPlantDetails] Details retrieved successfully\n";
        
        return details.str();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "[NurseryFacade::getPlantDetails] ERROR: " << e.what() << "\n";
        throw std::invalid_argument("Invalid SKU: " + sku);
    }
}

/**
 * @brief Build a default plant package for a given SKU
 * @param f Pointer to PlantKitFactory
 * @param id SKU identifier
 * @return Pointer to constructed CustomPlantPackage
 */
CustomPlantPackage* NurseryFacade::buildDefaultPackage(PlantKitFactory* f, const std::string& id)
{
    std::cout << "\n[NurseryFacade::buildDefaultPackage] Building package for " << id << "...\n";
    
    if (!f) 
    {
        throw std::invalid_argument("Factory cannot be null");
    }
    
    DummyPackageDirector* dummyDirector = dynamic_cast<DummyPackageDirector*>(director);
    
    if (dummyDirector) 
    {
        dummyDirector->construct();
    }
    
    std::cout << "[NurseryFacade::buildDefaultPackage] Package construction delegated to director\n";
    
    return nullptr; 
}

/**
 * @brief Generate receipt for customer order
 * @param custId Customer ID
 * @param items Vector of OrderItems
 * @return Formatted receipt string
 */
std::string NurseryFacade::generateReceipt(const std::string& custId, const std::vector<OrderItem*>& items)
{
    std::cout << "\n[NurseryFacade::generateReceipt] Generating receipt for " << custId << "...\n";
    
    std::ostringstream receipt;
    
    receipt << "----------------------------------------\n";
    receipt << "      PLANT NURSERY - ORDER RECEIPT      \n";
    receipt << "----------------------------------------\n\n";
    receipt << "Customer ID: " << custId << "\n";
    receipt << "Date: temp date function?\n";
    receipt << "----------------------------------------\n\n";
    receipt << "ITEMS:\n";
    
    double subtotal = 0.0;
    
    for (const auto& item : items) 
    {
        DummyOrderItem* dummyItem = dynamic_cast<DummyOrderItem*>(item);
        
        if (dummyItem) 
        {
            receipt << std::left << std::setw(30) << dummyItem->id;
            receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << dummyItem->price << "\n";
            
            subtotal += dummyItem->price;
        }
    }
    
    double tax = subtotal * 0.15;
    double total = subtotal + tax;
    
    receipt << "\n----------------------------------------\n";
    receipt << std::left << std::setw(30) << "Subtotal:";
    receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << subtotal << "\n";
    receipt << std::left << std::setw(30) << "VAT (15%):";
    receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << tax << "\n";
    receipt << std::left << std::setw(30) << "TOTAL:";
    receipt << "R" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << total << "\n";
    receipt << "----------------------------------------\n";
    receipt << "     Thank you for your purchase!       \n";
    receipt << "----------------------------------------\n";

    std::cout << "[NurseryFacade::generateReceipt] Receipt generated successfully\n";
    
    return receipt.str();
}

/**
 * @brief Place an order for a customer
 * @param custId Customer ID
 * @param items Vector of OrderItems
 */
void NurseryFacade::placeOrder(const std::string& custId, const std::vector<OrderItem*>& items)
{
    std::cout << "\n[NurseryFacade::placeOrder] *** SHOWCASE METHOD ***\n";
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
    
    // STEP 1: VALIDATION
    std::cout << "\n--- STEP 1: VALIDATION ---\n";
    
    for (const auto& item : items) 
    {
        DummyOrderItem* dummyItem = dynamic_cast<DummyOrderItem*>(item);
        
        if (!dummyItem) 
        {
            throw std::runtime_error("Invalid order item");
        }
        
        // Validate SKU exists in catalog FIRST
        if (!dummyCatalog->hasSKU(dummyItem->id)) 
        {
            throw std::invalid_argument("Invalid SKU: " + dummyItem->id);
        }
        
        // Check stock level
        int stock = dummyInv->available(dummyItem->id);
        std::cout << "  Checking " << dummyItem->id << ": stock=" << stock << "\n";
        
        if (stock <= 0) 
        {
            throw std::runtime_error("Insufficient stock for item: " + dummyItem->id);
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
    
    if (!dummySales->customerExists(custId)) 
    {
        throw std::invalid_argument("Invalid customer ID: " + custId);
    }
    
    std::cout << "  ✓ All validations passed\n";
    
    // STEP 2: CREATE ORDER
    std::cout << "\n--- STEP 2: CREATE ORDER ---\n";
    std::string orderId = dummySales->createOrder(custId, items);
    std::cout << "  ✓ Order created: " << orderId << "\n";
    
    // STEP 3: UPDATE INVENTORY
    std::cout << "\n--- STEP 3: UPDATE INVENTORY ---\n";
    
    for (const auto& item : items) 
    {
        DummyOrderItem* dummyItem = dynamic_cast<DummyOrderItem*>(item);
        
        if (dummyItem) 
        {
            bool success = dummyInv->consume(dummyItem->id, dummyItem->quantity);
            
            if (!success) 
            {
                throw std::runtime_error("Failed to consume inventory for: " + dummyItem->id);
            }
            
            std::cout << "  ✓ Consumed " << dummyItem->quantity << " unit(s) of " << dummyItem->id << "\n";
        }
    }
    
    // STEP 4: AUTOMATIC NOTIFICATIONS
    std::cout << "\n--- STEP 4: AUTOMATIC NOTIFICATIONS ---\n";
    std::cout << "  : SalesService notifies observers with OrderEvent\n";
    std::cout << "  : InventoryService notifies observers with StockEvent\n";
    std::cout << "  : NurseryHub receives notifications (Mediator pattern)\n";
    std::cout << "  : StaffDashboard updated automatically\n";
    
    std::cout << "\n[NurseryFacade::placeOrder] ✓ Order completed successfully!\n";
    std::cout << "  Order ID: " << orderId << "\n";
    std::cout << "  Items processed: " << items.size() << "\n";
    std::cout << "  Status: PENDING\n";
}

// staff operations

/**
 * @brief Restock inventory for a specific SKU
 * @param sku SKU of the plant
 * @param qty Quantity to restock
 */
void NurseryFacade::restock(const std::string& sku, int qty) 
{
    std::cout << "\n[NurseryFacade::restock] Restocking " << sku << " with " << qty << " units...\n";
    
    if (qty <= 0) 
    {
        throw std::invalid_argument("Restock quantity must be positive");
    }
    
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        throw std::runtime_error("Invalid subsystems");
    }
    
    if (!dummyCatalog->hasSKU(sku)) 
    {
        throw std::invalid_argument("Invalid SKU: " + sku);
    }
    
    dummyInv->restock(sku, qty);
    
    std::cout << "[NurseryFacade::restock] ✓ Restocking complete\n";
}

/**
 * @brief Get list of plants ready for sale
 * @return Vector of SKUs for plants ready to sell
 */
std::vector<std::string> NurseryFacade::getReadyForSale() 
{
    std::cout << "\n[NurseryFacade::getReadyForSale] Finding sellable plants...\n";
    
    std::vector<std::string> ready;
    
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    
    if (!dummyInv) 
    {
        std::cerr << "[NurseryFacade::getReadyForSale] ERROR: Invalid inventory service\n";
        return ready;
    }
    
    std::vector<DummyPlant*> allPlants = dummyInv->getAllPlants();
    
    std::cout << "  Checking " << allPlants.size() << " plants...\n";
    
    for (const auto& plant : allPlants) 
    {
        if (!plant) continue;
        
        int stock = dummyInv->available(plant->getId());
        
        if (stock > 0) 
        {
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
    
    std::cout << "[NurseryFacade::getReadyForSale] Found " << ready.size() << " plants ready for sale\n";
    
    return ready;
}

/**
 * @brief Check if specific plant is available for purchase
 * @param sku SKU to check
 * @return true if in stock AND in sellable state
 */
bool NurseryFacade::isAvailableForPurchase(const std::string& sku) 
{
    std::cout << "\n[NurseryFacade::isAvailableForPurchase] Checking " << sku << "...\n";
    
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    
    if (!dummyInv) return false;
    
    try 
    {
        int stock = dummyInv->available(sku);
        std::cout << "  Stock: " << stock << "\n";
        
        if (stock <= 0) 
        {
            std::cout << "  ✗ Out of stock\n";
            return false;
        }
        
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
 * @brief Validate stock for a SKU
 * @param sku SKU identifier
 * @param requiredQty Quantity required
 * @return "AVAILABLE", "PARTIAL", "UNAVAILABLE", or "INVALID_SKU"
 */
std::string NurseryFacade::validateStock(const std::string& sku, int requiredQty) 
{
    std::cout << "\n[NurseryFacade::validateStock] Validating " << sku << " (need " << requiredQty << ")...\n";
    
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (!dummyInv || !dummyCatalog) 
    {
        return "ERROR";
    }
    
    if (!dummyCatalog->hasSKU(sku)) 
    {
        std::cout << "  ✗ Invalid SKU\n";
        return "INVALID_SKU";
    }
    
    int currentStock = dummyInv->available(sku);
    std::cout << "  Current stock: " << currentStock << "\n";
    
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
 * @brief Generate inventory summary report
 * @return Formatted summary string
 */
std::string NurseryFacade::getInventorySummary() 
{
    std::cout << "\n[NurseryFacade::getInventorySummary] Generating summary...\n";
    
    std::ostringstream summary;
    
    DummyInventoryService* dummyInv = dynamic_cast<DummyInventoryService*>(inv);
    
    if (!dummyInv) 
    {
        return "ERROR: Invalid inventory service";
    }
    
    std::vector<DummyPlant*> allPlants = dummyInv->getAllPlants();
    std::vector<std::string> allSKUs = dummyInv->getAllSKUs();
    
    int totalSKUs = allSKUs.size();
    int readyForSale = 0;
    int lowStock = 0;
    int outOfStock = 0;
    
    std::vector<std::pair<std::string, int>> lowStockItems;
    std::vector<std::string> outOfStockItems;
    
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
    
    summary << "===== INVENTORY SUMMARY =====\n";
    summary << "Total SKUs: " << totalSKUs << "\n";
    summary << "Ready for Sale: " << readyForSale << "\n";
    summary << "Low Stock (<5): " << lowStock << "\n";
    summary << "Out of Stock: " << outOfStock << "\n";
    
    if (!lowStockItems.empty()) 
    {
        summary << "\nLOW STOCK ALERTS:\n";
        for (const auto& item : lowStockItems) 
        {
            summary << "  - " << item.first << ": " << item.second << " remaining\n";
        }
    }
    
    if (!outOfStockItems.empty()) 
    {
        summary << "\nOUT OF STOCK:\n";
        for (const auto& sku : outOfStockItems) 
        {
            summary << "  - " << sku << "\n";
        }
    }
    
    summary << "=============================\n";
    
    std::cout << "[NurseryFacade::getInventorySummary] Summary generated\n";
    
    return summary.str();
}

//operations general to both sections

/**
 * @brief Check if all subsystems are valid
 * @return true if all subsystems are valid
 */
bool NurseryFacade::isValid() const 
{
    return areSubsystemsValid();
}

/**
 * @brief Get all available SKUs in catalog
 * @return Vector of SKU strings
 */
std::vector<std::string> NurseryFacade::getAllSKUs() const 
{
    DummySpeciesCatalog* dummyCatalog = dynamic_cast<DummySpeciesCatalog*>(catalog);
    
    if (dummyCatalog) 
    {
        return dummyCatalog->getAllSKUs();
    }
    
    return std::vector<std::string>();
}

/**
 * @brief Check if all subsystems are valid
 * @return true if all subsystems are valid
 */
bool NurseryFacade::areSubsystemsValid() const 
{
    return catalog != nullptr && 
           inv != nullptr && 
           sales != nullptr && 
           factory != nullptr && 
           director != nullptr;
}