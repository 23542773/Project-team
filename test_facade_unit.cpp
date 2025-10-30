#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Include unified facade
#include "NurseryFacade.h"

// Include dummy implementations for testing
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
 * @file test_facade_unit.cpp
 * @brief Unit tests for unified Facade pattern using Google Test framework
 * @author Damian Moustakis - COS 214 Project
 * @author Locutus-0201
 * @date 2025-10-30 11:31:27 UTC
 * 
 * TRUE UNIT TESTING:
 * - Tests individual facade methods in isolation
 * - Uses real dummy implementations (no mocks needed yet)
 * - Each test focuses on specific behavior
 * - Fast, focused, independent tests
 */

// ============================================================================
//                          TEST FIXTURES
// ============================================================================

/**
 * @class FacadeTest
 * @brief Test fixture for unified NurseryFacade
 * 
 * Sets up fresh subsystems and facade for each test
 */
class FacadeTest : public ::testing::Test 
{
    protected:
        // Test subsystems
        DummySpeciesCatalog* catalog;
        DummyInventoryService* inv;
        DummySalesService* sales;
        DummyPlantKitFactory* factory;
        DummyPackageDirector* director;
        
        // Unified facade under test
        NurseryFacade* facade;

        /**
         * @brief Set up before each test
         * Creates fresh subsystems and facade
         */
        void SetUp() override 
        {
            catalog = new DummySpeciesCatalog();
            inv = new DummyInventoryService();
            sales = new DummySalesService();
            factory = new DummyPlantKitFactory("Indoor");
            director = new DummyPackageDirector(nullptr);

            facade = new NurseryFacade(catalog, factory, director, inv, sales);
            
            // Add test plants
            addTestPlants();
        }

        /**
         * @brief Clean up after each test
         * Deletes facade and subsystems
         */
        void TearDown() override 
        {
            delete facade;
            delete catalog;
            delete inv;
            delete sales;
            delete factory;
            delete director;
        }

        /**
         * @brief Helper: Add test plants to inventory
         */
        void addTestPlants() 
        {
            // SUCC-001: Mature plant (can sell)
            DummyPlantFlyweight* aloe = catalog->getBySKU("SUCC-001");
            inv->addPlant("SUCC-001", new DummyPlant("SUCC-001", aloe, new DummyMatureState()));
            
            // CACT-001: Seedling (cannot sell)
            DummyPlantFlyweight* cactus = catalog->getBySKU("CACT-001");
            inv->addPlant("CACT-001", new DummyPlant("CACT-001", cactus, new DummySeedlingState()));
        }
};

// ============================================================================
//                    CUSTOMER OPERATION TESTS
// ============================================================================

TEST_F(FacadeTest, IsValid_WithAllSubsystems_ReturnsTrue) 
{
    EXPECT_TRUE(facade->isValid());
}

TEST_F(FacadeTest, BrowseAvailable_WithValidSKUs_ReturnsAvailablePlants) 
{
    std::vector<std::string> skus = {"SUCC-001", "CACT-001"};
    auto result = facade->browseAvailable(skus);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result[0].find("Aloe Vera") != std::string::npos);
    EXPECT_TRUE(result[1].find("Desert Rose") != std::string::npos);
}

TEST_F(FacadeTest, BrowseAvailable_WithOutOfStockSKU_ExcludesIt) 
{
    while (inv->available("SUCC-001") > 0) 
    {
        inv->consume("SUCC-001", 1);
    }
    
    std::vector<std::string> skus = {"SUCC-001", "CACT-001"};
    auto result = facade->browseAvailable(skus);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].find("CACT-001") != std::string::npos);
}

TEST_F(FacadeTest, BrowseAvailable_WithInvalidSKU_ExcludesIt) 
{
    std::vector<std::string> skus = {"SUCC-001", "INVALID-999"};
    auto result = facade->browseAvailable(skus);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].find("SUCC-001") != std::string::npos);
}

TEST_F(FacadeTest, GetPlantDetails_WithValidSKU_ReturnsDetails) 
{
    std::string details = facade->getPlantDetails("SUCC-001");
    
    EXPECT_FALSE(details.empty());
    EXPECT_TRUE(details.find("Aloe Vera") != std::string::npos);
    EXPECT_TRUE(details.find("Indoor") != std::string::npos);
    EXPECT_TRUE(details.find("250ml") != std::string::npos);
    EXPECT_TRUE(details.find("8 hours") != std::string::npos);
}

TEST_F(FacadeTest, GetPlantDetails_WithInvalidSKU_ThrowsException) 
{
    EXPECT_THROW({
        facade->getPlantDetails("INVALID-999");
    }, std::invalid_argument);
}

TEST_F(FacadeTest, GenerateReceipt_WithMultipleItems_CalculatesTotalCorrectly) 
{
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    items.push_back(new DummyOrderItem("HERB-023", 85.00, "plant", 1));
    
    std::string receipt = facade->generateReceipt("CUST-001", items);
    
    EXPECT_FALSE(receipt.empty());
    EXPECT_TRUE(receipt.find("SUCC-001") != std::string::npos);
    EXPECT_TRUE(receipt.find("HERB-023") != std::string::npos);
    EXPECT_TRUE(receipt.find("235.00") != std::string::npos);  // Subtotal
    EXPECT_TRUE(receipt.find("270.25") != std::string::npos);  // Total with VAT
    
    for (auto item : items) delete item;
}

TEST_F(FacadeTest, PlaceOrder_WithValidItems_UpdatesInventory) 
{
    int beforeStock = inv->available("SUCC-001");
    
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    
    EXPECT_NO_THROW({
        facade->placeOrder("CUST-001", items);
    });
    
    int afterStock = inv->available("SUCC-001");
    EXPECT_EQ(afterStock, beforeStock - 1);
    
    for (auto item : items) delete item;
}

TEST_F(FacadeTest, PlaceOrder_WithInsufficientStock_ThrowsException) 
{
    while (inv->available("SUCC-001") > 0) 
    {
        inv->consume("SUCC-001", 1);
    }
    
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    
    EXPECT_THROW({
        facade->placeOrder("CUST-001", items);
    }, std::runtime_error);
    
    for (auto item : items) delete item;
}

TEST_F(FacadeTest, PlaceOrder_WithInvalidCustomer_ThrowsException) 
{
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    
    EXPECT_THROW({
        facade->placeOrder("INVALID-CUST", items);
    }, std::invalid_argument);
    
    for (auto item : items) delete item;
}

TEST_F(FacadeTest, PlaceOrder_WithInvalidSKU_ThrowsException) 
{
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("INVALID-999", 150.00, "plant", 1));
    
    EXPECT_THROW({
        facade->placeOrder("CUST-001", items);
    }, std::invalid_argument);
    
    for (auto item : items) delete item;
}

// ============================================================================
//                      STAFF OPERATION TESTS
// ============================================================================

TEST_F(FacadeTest, Restock_WithValidSKU_IncreasesStock) 
{
    int beforeStock = inv->available("SUCC-001");
    
    EXPECT_NO_THROW({
        facade->restock("SUCC-001", 10);
    });
    
    int afterStock = inv->available("SUCC-001");
    EXPECT_EQ(afterStock, beforeStock + 10);
}

TEST_F(FacadeTest, Restock_WithNegativeQuantity_ThrowsException) 
{
    EXPECT_THROW({
        facade->restock("SUCC-001", -5);
    }, std::invalid_argument);
}

TEST_F(FacadeTest, Restock_WithZeroQuantity_ThrowsException) 
{
    EXPECT_THROW({
        facade->restock("SUCC-001", 0);
    }, std::invalid_argument);
}

TEST_F(FacadeTest, Restock_WithInvalidSKU_ThrowsException) 
{
    EXPECT_THROW({
        facade->restock("INVALID-999", 10);
    }, std::invalid_argument);
}

TEST_F(FacadeTest, GetReadyForSale_ReturnsMaturePlantsOnly) 
{
    auto ready = facade->getReadyForSale();
    
    EXPECT_GE(ready.size(), 1);
    
    bool hasSUCC = std::find(ready.begin(), ready.end(), "SUCC-001") != ready.end();
    bool hasCACT = std::find(ready.begin(), ready.end(), "CACT-001") != ready.end();
    
    EXPECT_TRUE(hasSUCC);   // SUCC-001 is mature
    EXPECT_FALSE(hasCACT);  // CACT-001 is seedling
}

TEST_F(FacadeTest, IsAvailableForPurchase_MaturePlant_ReturnsTrue) 
{
    bool available = facade->isAvailableForPurchase("SUCC-001");
    EXPECT_TRUE(available);
}

TEST_F(FacadeTest, IsAvailableForPurchase_SeedlingPlant_ReturnsFalse) 
{
    bool available = facade->isAvailableForPurchase("CACT-001");
    EXPECT_FALSE(available);
}

TEST_F(FacadeTest, ValidateStock_SufficientQuantity_ReturnsAvailable) 
{
    std::string status = facade->validateStock("SUCC-001", 10);
    EXPECT_EQ(status, "AVAILABLE");
}

TEST_F(FacadeTest, ValidateStock_PartialQuantity_ReturnsPartial) 
{
    std::string status = facade->validateStock("SUCC-001", 20);
    EXPECT_EQ(status, "PARTIAL");
}

TEST_F(FacadeTest, ValidateStock_NoStock_ReturnsUnavailable) 
{
    while (inv->available("SUCC-001") > 0) 
    {
        inv->consume("SUCC-001", 1);
    }
    
    std::string status = facade->validateStock("SUCC-001", 1);
    EXPECT_EQ(status, "UNAVAILABLE");
}

TEST_F(FacadeTest, ValidateStock_InvalidSKU_ReturnsInvalidSKU) 
{
    std::string status = facade->validateStock("INVALID-999", 10);
    EXPECT_EQ(status, "INVALID_SKU");
}

TEST_F(FacadeTest, GetInventorySummary_ContainsExpectedInfo) 
{
    std::string summary = facade->getInventorySummary();
    
    EXPECT_FALSE(summary.empty());
    EXPECT_TRUE(summary.find("Total SKUs") != std::string::npos);
    EXPECT_TRUE(summary.find("Ready for Sale") != std::string::npos);
    EXPECT_TRUE(summary.find("Low Stock") != std::string::npos);
    EXPECT_TRUE(summary.find("Out of Stock") != std::string::npos);
}

// ============================================================================
//                      SHARED OPERATION TESTS
// ============================================================================

TEST_F(FacadeTest, GetAllSKUs_ReturnsAllCatalogSKUs) 
{
    auto skus = facade->getAllSKUs();
    
    EXPECT_GT(skus.size(), 0);
    EXPECT_TRUE(std::find(skus.begin(), skus.end(), "SUCC-001") != skus.end());
}

// ============================================================================
//                              MAIN
// ============================================================================

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}