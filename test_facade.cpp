#include <iostream>
#include <vector>
#include <exception>

// Include unified facade
#include "NurseryFacade.h"

// Include dummy subsystems
#include "DummySpeciesCatalog.h"
#include "DummyInventoryService.h"
#include "DummySalesService.h"
#include "DummyPlantKitFactory.h"
#include "DummyPackageDirector.h"
#include "DummyOrderItem.h"
#include "DummyPlant.h"
#include "DummyPlantState.h"
#include "DummyPlantFlyweight.h"

/**
 * @file test_facade.cpp
 * @brief Comprehensive integration test for unified Facade pattern
 * @author Damian Moustakis - COS 214 Project
 * @author Locutus-0201
 * @date 2025-10-30 11:31:27 UTC
 */

void printSeparator(const std::string& title) 
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "========================================\n";
}

void printTestResult(const std::string& testName, bool passed) 
{
    std::cout << "\n[TEST] " << testName << ": ";
    if (passed) 
    {
        std::cout << "✓ PASSED\n";
    } 
    else 
    {
        std::cout << "✗ FAILED\n";
    }
}

int main() 
{
    printSeparator("UNIFIED FACADE TESTING");
    
    int testsPassed = 0;
    int totalTests = 0;
    
    try 
    {
        // ====================================================================
        // SETUP: Create dummy subsystems
        // ====================================================================
        printSeparator("SETUP: Creating Subsystems");
        
        std::cout << "Creating DummySpeciesCatalog...\n";
        DummySpeciesCatalog* catalog = new DummySpeciesCatalog();
        
        std::cout << "Creating DummyInventoryService...\n";
        DummyInventoryService* inv = new DummyInventoryService();
        
        std::cout << "Creating DummySalesService...\n";
        DummySalesService* sales = new DummySalesService();
        
        std::cout << "Creating DummyPlantKitFactory (Indoor)...\n";
        DummyPlantKitFactory* factory = new DummyPlantKitFactory("Indoor");
        
        std::cout << "Creating DummyPackageDirector...\n";
        DummyPackageDirector* director = new DummyPackageDirector(nullptr);

        // Add some plants to inventory with different states for testing
        std::cout << "\nAdding plants to inventory...\n";
        
        // SUCC-001: Aloe Vera (MATURE - can be sold)
        DummyPlantFlyweight* aloeSpecies = catalog->getBySKU("SUCC-001");
        DummyPlant* plant1 = new DummyPlant("SUCC-001", aloeSpecies, new DummyMatureState());
        inv->addPlant("SUCC-001", plant1);
        std::cout << "  Added SUCC-001 (Aloe Vera) - MATURE state\n";

        // CACT-001: Desert Rose (SEEDLING - cannot be sold)
        DummyPlantFlyweight* cactusSpecies = catalog->getBySKU("CACT-001");
        DummyPlant* plant2 = new DummyPlant("CACT-001", cactusSpecies, new DummySeedlingState());
        inv->addPlant("CACT-001", plant2);
        std::cout << "  Added CACT-001 (Desert Rose) - SEEDLING state\n";

        // ORCH-001: Orchid (MATURE - can be sold)
        DummyPlantFlyweight* orchidSpecies = catalog->getBySKU("ORCH-001");
        DummyPlant* plant3 = new DummyPlant("ORCH-001", orchidSpecies, new DummyMatureState());
        inv->addPlant("ORCH-001", plant3);
        std::cout << "  Added ORCH-001 (Orchid) - MATURE state\n";

        // ====================================================================
        // CREATE UNIFIED FACADE
        // ====================================================================
        printSeparator("Creating Unified Facade");
        
        std::cout << "Creating NurseryFacade...\n";
        NurseryFacade facade(catalog, factory, director, inv, sales);

        // ====================================================================
        // TEST 1: Facade Validation
        // ====================================================================
        printSeparator("TEST 1: Facade Validation");
        totalTests++;
        
        bool facadeValid = facade.isValid();
        
        std::cout << "Facade valid: " << (facadeValid ? "YES" : "NO") << "\n";
        
        bool test1Passed = facadeValid;
        printTestResult("Facade Validation", test1Passed);
        if (test1Passed) testsPassed++;

        // ====================================================================
        // TEST 2: Browse Available Plants (Customer Operation)
        // ====================================================================
        printSeparator("TEST 2: Browse Available Plants");
        totalTests++;
        
        std::vector<std::string> skus = {"SUCC-001", "CACT-001", "ORCH-001", "HERB-023", "INVALID-SKU"};
        std::cout << "Browsing SKUs: ";
        for (const auto& sku : skus) 
        {
            std::cout << sku << " ";
        }
        std::cout << "\n";
        
        auto available = facade.browseAvailable(skus);
        
        std::cout << "\n--- RESULTS ---\n";
        std::cout << "Available plants found: " << available.size() << "\n";
        for (const auto& item : available) 
        {
            std::cout << "  • " << item << "\n";
        }
        
        bool test2Passed = (available.size() > 0);
        printTestResult("Browse Available Plants", test2Passed);
        if (test2Passed) testsPassed++;

        // ====================================================================
        // TEST 3: Get Plant Details (Customer Operation)
        // ====================================================================
        printSeparator("TEST 3: Get Plant Details");
        totalTests++;
        
        try 
        {
            std::string details = facade.getPlantDetails("SUCC-001");
            std::cout << "\n--- PLANT DETAILS ---\n";
            std::cout << details << "\n";
            
            bool test3Passed = (!details.empty() && details.find("Aloe Vera") != std::string::npos);
            printTestResult("Get Plant Details", test3Passed);
            if (test3Passed) testsPassed++;
        } 
        catch (const std::exception& e) 
        {
            std::cout << "ERROR: " << e.what() << "\n";
            printTestResult("Get Plant Details", false);
        }

        // ====================================================================
        // TEST 4: Check Available for Purchase (Staff Operation)
        // ====================================================================
        printSeparator("TEST 4: Check Available for Purchase");
        totalTests++;
        
        bool canBuyAloe = facade.isAvailableForPurchase("SUCC-001");
        bool canBuyCactus = facade.isAvailableForPurchase("CACT-001");
        
        std::cout << "\n--- RESULTS ---\n";
        std::cout << "SUCC-001 (Aloe - MATURE): " << (canBuyAloe ? "✓ CAN BUY" : "✗ CANNOT BUY") << "\n";
        std::cout << "CACT-001 (Cactus - SEEDLING): " << (canBuyCactus ? "✓ CAN BUY" : "✗ CANNOT BUY") << "\n";
        
        bool test4Passed = (canBuyAloe == true && canBuyCactus == false);
        printTestResult("Available for Purchase (State Check)", test4Passed);
        if (test4Passed) testsPassed++;

        // ====================================================================
        // TEST 5: Restock Operation (Staff Operation)
        // ====================================================================
        printSeparator("TEST 5: Staff Restock Operation");
        totalTests++;
        
        try 
        {
            int beforeStock = inv->available("ORCH-001");
            std::cout << "Before restock: ORCH-001 = " << beforeStock << " units\n";
            
            facade.restock("ORCH-001", 10);
            
            int afterStock = inv->available("ORCH-001");
            std::cout << "After restock: ORCH-001 = " << afterStock << " units\n";
            
            bool test5Passed = (afterStock == beforeStock + 10);
            printTestResult("Staff Restock Operation", test5Passed);
            if (test5Passed) testsPassed++;
        } 
        catch (const std::exception& e) 
        {
            std::cout << "ERROR: " << e.what() << "\n";
            printTestResult("Staff Restock Operation", false);
        }

        // ====================================================================
        // TEST 6: Get Ready for Sale (Staff Operation)
        // ====================================================================
        printSeparator("TEST 6: Get Plants Ready for Sale");
        totalTests++;
        
        auto readyPlants = facade.getReadyForSale();
        
        std::cout << "\n--- RESULTS ---\n";
        std::cout << "Plants ready for sale: " << readyPlants.size() << "\n";
        for (const auto& sku : readyPlants) 
        {
            std::cout << "  • " << sku << "\n";
        }
        
        bool test6Passed = (readyPlants.size() >= 2);  // Should have SUCC-001 and ORCH-001
        printTestResult("Get Ready for Sale", test6Passed);
        if (test6Passed) testsPassed++;

        // ====================================================================
        // TEST 7: Validate Stock (Staff Operation)
        // ====================================================================
        printSeparator("TEST 7: Validate Stock");
        totalTests++;
        
        std::string status1 = facade.validateStock("SUCC-001", 20);
        std::string status2 = facade.validateStock("SUCC-001", 10);
        std::string status3 = facade.validateStock("INVALID", 5);
        
        std::cout << "\n--- RESULTS ---\n";
        std::cout << "SUCC-001 (need 20): " << status1 << "\n";
        std::cout << "SUCC-001 (need 10): " << status2 << "\n";
        std::cout << "INVALID (need 5): " << status3 << "\n";
        
        bool test7Passed = (status3 == "INVALID_SKU");
        printTestResult("Validate Stock", test7Passed);
        if (test7Passed) testsPassed++;

        // ====================================================================
        // TEST 8: Inventory Summary (Staff Operation)
        // ====================================================================
        printSeparator("TEST 8: Inventory Summary");
        totalTests++;
        
        std::string summary = facade.getInventorySummary();
        
        std::cout << "\n--- INVENTORY SUMMARY ---\n";
        std::cout << summary << "\n";
        
        bool test8Passed = (!summary.empty() && summary.find("Total SKUs") != std::string::npos);
        printTestResult("Inventory Summary", test8Passed);
        if (test8Passed) testsPassed++;

        // ====================================================================
        // TEST 9: Generate Receipt (Customer Operation)
        // ====================================================================
        printSeparator("TEST 9: Generate Order Receipt");
        totalTests++;
        
        std::vector<OrderItem*> receiptItems;
        receiptItems.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
        receiptItems.push_back(new DummyOrderItem("HERB-023", 85.00, "plant", 1));
        
        std::string receipt = facade.generateReceipt("CUST-001", receiptItems);
        
        std::cout << "\n--- RECEIPT ---\n";
        std::cout << receipt << "\n";
        
        bool test9Passed = (!receipt.empty() && receipt.find("TOTAL") != std::string::npos);
        printTestResult("Generate Receipt", test9Passed);
        if (test9Passed) testsPassed++;
        
        // Cleanup receipt items
        for (auto item : receiptItems) 
        {
            delete item;
        }
        receiptItems.clear();

        // ====================================================================
        // TEST 10: Place Order (Customer Operation - SHOWCASE)
        // ====================================================================
        printSeparator("TEST 10: Place Order (SHOWCASE)");
        totalTests++;
        
        std::vector<OrderItem*> orderItems;
        orderItems.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
        orderItems.push_back(new DummyOrderItem("HERB-023", 85.00, "plant", 1));
        
        try 
        {
            int beforeStock = inv->available("SUCC-001");
            std::cout << "Before order: SUCC-001 stock = " << beforeStock << "\n\n";
            
            facade.placeOrder("CUST-001", orderItems);
            
            int afterStock = inv->available("SUCC-001");
            std::cout << "\nAfter order: SUCC-001 stock = " << afterStock << "\n";
            
            bool test10Passed = (afterStock == beforeStock - 1);
            printTestResult("Place Order (Stock Updated)", test10Passed);
            if (test10Passed) testsPassed++;
        } 
        catch (const std::exception& e) 
        {
            std::cout << "\nERROR: " << e.what() << "\n";
            printTestResult("Place Order", false);
        }
        
        // Cleanup order items
        for (auto item : orderItems) 
        {
            delete item;
        }

        // ====================================================================
        // TEST 11: Error Handling - Invalid SKU
        // ====================================================================
        printSeparator("TEST 11: Error Handling");
        totalTests++;
        
        bool exceptionThrown = false;
        try 
        {
            facade.getPlantDetails("NONEXISTENT-SKU");
        } 
        catch (const std::invalid_argument& e) 
        {
            std::cout << "Expected exception caught: " << e.what() << "\n";
            exceptionThrown = true;
        }
        
        printTestResult("Error Handling (Invalid SKU)", exceptionThrown);
        if (exceptionThrown) testsPassed++;

        // ====================================================================
        // TEST 12: Error Handling - Insufficient Stock
        // ====================================================================
        printSeparator("TEST 12: Insufficient Stock Handling");
        totalTests++;
        
        bool insufficientStockHandled = false;
        
        // Set FERN-005 to 0 stock
        while (inv->available("FERN-005") > 0) 
        {
            inv->consume("FERN-005", 1);
        }
        std::cout << "Set FERN-005 to 0 stock\n";
        
        std::vector<OrderItem*> badOrder;
        badOrder.push_back(new DummyOrderItem("FERN-005", 100.00, "plant", 1));
        
        try 
        {
            facade.placeOrder("CUST-001", badOrder);
        } 
        catch (const std::runtime_error& e) 
        {
            std::cout << "Expected exception caught: " << e.what() << "\n";
            insufficientStockHandled = true;
        }
        
        // Cleanup
        for (auto item : badOrder) 
        {
            delete item;
        }
        
        printTestResult("Insufficient Stock Handling", insufficientStockHandled);
        if (insufficientStockHandled) testsPassed++;

        // ====================================================================
        // TEST 13: Get All SKUs (Shared Operation)
        // ====================================================================
        printSeparator("TEST 13: Get All SKUs");
        totalTests++;
        
        auto allSKUs = facade.getAllSKUs();
        
        std::cout << "\n--- ALL SKUs ---\n";
        std::cout << "Total SKUs: " << allSKUs.size() << "\n";
        for (const auto& sku : allSKUs) 
        {
            std::cout << "  • " << sku << "\n";
        }
        
        bool test13Passed = (allSKUs.size() > 0);
        printTestResult("Get All SKUs", test13Passed);
        if (test13Passed) testsPassed++;

        // ====================================================================
        // CLEANUP
        // ====================================================================
        printSeparator("CLEANUP: Destroying Subsystems");
        
        std::cout << "Deleting subsystems...\n";
        delete catalog;
        delete inv;
        delete sales;
        delete factory;
        delete director;
        
        std::cout << "Cleanup complete\n";

        // ====================================================================
        // FINAL RESULTS
        // ====================================================================
        printSeparator("TEST RESULTS SUMMARY");
        
        std::cout << "\n";
        std::cout << "Tests Passed: " << testsPassed << " / " << totalTests << "\n";
        std::cout << "Success Rate: " << (testsPassed * 100 / totalTests) << "%\n";
        
        if (testsPassed == totalTests) 
        {
            std::cout << "\n✓✓✓ ALL TESTS PASSED! ✓✓✓\n";
            std::cout << "\nUnified facade implementation is working correctly!\n";
            std::cout << "Ready to integrate real pattern implementations.\n";
        } 
        else 
        {
            std::cout << "\n⚠ Some tests failed. Review implementation.\n";
        }
        
        printSeparator("END OF TESTING");

    } 
    catch (const std::exception& e) 
    {
        std::cerr << "\n\n";
        std::cerr << "========================================\n";
        std::cerr << "  FATAL ERROR\n";
        std::cerr << "========================================\n";
        std::cerr << e.what() << "\n";
        std::cerr << "========================================\n";
        return 1;
    }

    return 0;
}