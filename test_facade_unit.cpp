#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Include facades
#include "CustomerNurseryFacade.h"
#include "StaffNurseryFacade.h"
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
 * @brief Unit tests for Facade pattern using Google Test framework
 * @author Damian Moustakis - COS 214 Project
 */

/**
 * @class CustomerFacadeTest
 * @brief Test fixture for CustomerNurseryFacade
 * 
 * Sets up fresh subsystems and facade for each test
 */
class CustomerFacadeTest : public ::testing::Test 
{
    protected:
        // Test subsystems
        DummySpeciesCatalog* catalog;
        DummyInventoryService* inv;
        DummySalesService* sales;
        DummyPlantKitFactory* factory;
        DummyPackageDirector* director;
        
        // Facade under test
        CustomerNurseryFacade* facade;

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

            facade = new CustomerNurseryFacade(catalog, factory, director, inv, sales);
            
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

/**
 * @class StaffFacadeTest
 * @brief Test fixture for StaffNurseryFacade
 */
class StaffFacadeTest : public ::testing::Test 
{
    protected:
        DummySpeciesCatalog* catalog;
        DummyInventoryService* inv;
        DummySalesService* sales;
        StaffNurseryFacade* facade;

        void SetUp() override 
        {
            catalog = new DummySpeciesCatalog();
            inv = new DummyInventoryService();
            sales = new DummySalesService();
            facade = new StaffNurseryFacade(catalog, inv, sales);
            
            addTestPlants();
        }

        void TearDown() override 
        {
            delete facade;
            delete catalog;
            delete inv;
            delete sales;
        }

        void addTestPlants() 
        {
            DummyPlantFlyweight* aloe = catalog->getBySKU("SUCC-001");
            inv->addPlant("SUCC-001", new DummyPlant("SUCC-001", aloe, new DummyMatureState()));
        }
};

//customer facade
/**
 * @test Verify facade validation works correctly
 */
TEST_F(CustomerFacadeTest, IsValid_WithAllSubsystems_ReturnsTrue) 
{
    // Test that facade correctly validates all subsystems are present
    EXPECT_TRUE(facade->isValid());
}

/**
 * @test Browse available plants with valid SKUs
 */
TEST_F(CustomerFacadeTest, BrowseAvailable_WithValidSKUs_ReturnsAvailablePlants) 
{
    // Arrange: Prepare list of SKUs to browse
    std::vector<std::string> skus = {"SUCC-001", "CACT-001"};
    
    // Act: Browse available plants
    auto result = facade->browseAvailable(skus);
    
    // Assert: Should return both plants (both have stock)
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result[0].find("Aloe Vera") != std::string::npos);
    EXPECT_TRUE(result[1].find("Desert Rose") != std::string::npos);
}

/**
 * @test Browse available with out-of-stock SKU
 */
TEST_F(CustomerFacadeTest, BrowseAvailable_WithOutOfStockSKU_ExcludesIt) 
{
    // Arrange: Deplete SUCC-001 stock
    while (inv->available("SUCC-001") > 0) 
    {
        inv->consume("SUCC-001", 1);
    }
    
    std::vector<std::string> skus = {"SUCC-001", "CACT-001"};
    
    // Act
    auto result = facade->browseAvailable(skus);
    
    // Assert: Should only return CACT-001 (still has stock)
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].find("CACT-001") != std::string::npos);
}

/**
 * @test Browse available with invalid SKU
 */
TEST_F(CustomerFacadeTest, BrowseAvailable_WithInvalidSKU_ExcludesIt) 
{
    // Arrange
    std::vector<std::string> skus = {"SUCC-001", "INVALID-999"};
    
    // Act
    auto result = facade->browseAvailable(skus);
    
    // Assert: Should only return valid SKU
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].find("SUCC-001") != std::string::npos);
}

/**
 * @test Get plant details for valid SKU
 */
TEST_F(CustomerFacadeTest, GetPlantDetails_WithValidSKU_ReturnsDetails) 
{
    // Act
    std::string details = facade->getPlantDetails("SUCC-001");
    
    // Assert: Should contain key information
    EXPECT_FALSE(details.empty());
    EXPECT_TRUE(details.find("Aloe Vera") != std::string::npos);
    EXPECT_TRUE(details.find("Indoor") != std::string::npos);
    EXPECT_TRUE(details.find("250ml") != std::string::npos);
    EXPECT_TRUE(details.find("8 hours") != std::string::npos);
}

/**
 * @test Get plant details for invalid SKU throws exception
 */
TEST_F(CustomerFacadeTest, GetPlantDetails_WithInvalidSKU_ThrowsException) 
{
    // Act & Assert: Should throw invalid_argument
    EXPECT_THROW({
        facade->getPlantDetails("INVALID-999");
    }, std::invalid_argument);
}

/**
 * @test Generate receipt with multiple items
 */
TEST_F(CustomerFacadeTest, OrderReceipt_WithMultipleItems_CalculatesTotalCorrectly) 
{
    // Arrange
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    items.push_back(new DummyOrderItem("HERB-023", 85.00, "plant", 1));
    
    // Act
    std::string receipt = facade->orderReceipt("CUST-001", items);
    
    // Assert
    EXPECT_FALSE(receipt.empty());
    EXPECT_TRUE(receipt.find("SUCC-001") != std::string::npos);
    EXPECT_TRUE(receipt.find("HERB-023") != std::string::npos);
    EXPECT_TRUE(receipt.find("235.00") != std::string::npos);  // Subtotal
    EXPECT_TRUE(receipt.find("270.25") != std::string::npos);  // Total with VAT
    
    // Cleanup
    for (auto item : items) delete item;
}

/**
 * @test Place order with valid items updates inventory
 */
TEST_F(CustomerFacadeTest, PlaceOrder_WithValidItems_UpdatesInventory) 
{
    // Arrange
    int beforeStock = inv->available("SUCC-001");
    
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    
    // Act
    EXPECT_NO_THROW({
        facade->placeOrder("CUST-001", items);
    });
    
    // Assert: Stock should decrease by 1
    int afterStock = inv->available("SUCC-001");
    EXPECT_EQ(afterStock, beforeStock - 1);
    
    // Cleanup
    for (auto item : items) delete item;
}

/**
 * @test Place order with insufficient stock throws exception
 */
TEST_F(CustomerFacadeTest, PlaceOrder_WithInsufficientStock_ThrowsException) 
{
    // Arrange: Deplete stock
    while (inv->available("SUCC-001") > 0) 
    {
        inv->consume("SUCC-001", 1);
    }
    
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    
    // Act & Assert: Should throw runtime_error
    EXPECT_THROW({
        facade->placeOrder("CUST-001", items);
    }, std::runtime_error);
    
    // Cleanup
    for (auto item : items) delete item;
}

/**
 * @test Place order with invalid customer throws exception
 */
TEST_F(CustomerFacadeTest, PlaceOrder_WithInvalidCustomer_ThrowsException) 
{
    // Arrange
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("SUCC-001", 150.00, "plant", 1));
    
    // Act & Assert: Should throw invalid_argument
    EXPECT_THROW({
        facade->placeOrder("INVALID-CUST", items);
    }, std::invalid_argument);
    
    // Cleanup
    for (auto item : items) delete item;
}

/**
 * @test Place order with invalid SKU throws exception
 */
TEST_F(CustomerFacadeTest, PlaceOrder_WithInvalidSKU_ThrowsException) 
{
    // Arrange
    std::vector<OrderItem*> items;
    items.push_back(new DummyOrderItem("INVALID-999", 150.00, "plant", 1));
    
    // Act & Assert
    EXPECT_THROW({
        facade->placeOrder("CUST-001", items);
    }, std::invalid_argument);
    
    // Cleanup
    for (auto item : items) delete item;
}

//staff facade
/**
 * @test Verify staff facade validation
 */
TEST_F(StaffFacadeTest, IsValid_WithAllSubsystems_ReturnsTrue) 
{
    EXPECT_TRUE(facade->isValid());
}

/**
 * @test Restock with valid SKU increases stock
 */
TEST_F(StaffFacadeTest, Restock_WithValidSKU_IncreasesStock) 
{
    // Arrange
    int beforeStock = inv->available("SUCC-001");
    
    // Act
    EXPECT_NO_THROW({
        facade->restock("SUCC-001", 10);
    });
    
    // Assert: Stock should increase by 10
    int afterStock = inv->available("SUCC-001");
    EXPECT_EQ(afterStock, beforeStock + 10);
}

/**
 * @test Restock with negative quantity throws exception
 */
TEST_F(StaffFacadeTest, Restock_WithNegativeQuantity_ThrowsException) 
{
    // Act & Assert
    EXPECT_THROW({
        facade->restock("SUCC-001", -5);
    }, std::invalid_argument);
}

/**
 * @test Restock with zero quantity throws exception
 */
TEST_F(StaffFacadeTest, Restock_WithZeroQuantity_ThrowsException) 
{
    // Act & Assert
    EXPECT_THROW({
        facade->restock("SUCC-001", 0);
    }, std::invalid_argument);
}

/**
 * @test Restock with invalid SKU throws exception
 */
TEST_F(StaffFacadeTest, Restock_WithInvalidSKU_ThrowsException) 
{
    // Act & Assert
    EXPECT_THROW({
        facade->restock("INVALID-999", 10);
    }, std::invalid_argument);
}

/**
 * @test Get ready for sale returns only mature plants
 */
TEST_F(StaffFacadeTest, GetReadyForSale_ReturnsMaturePlantsOnly) 
{
    // Arrange: Add another plant in seedling state
    DummyPlantFlyweight* cactus = catalog->getBySKU("CACT-001");
    inv->addPlant("CACT-001", new DummyPlant("CACT-001", cactus, new DummySeedlingState()));
    
    // Act
    auto ready = facade->getReadyForSale();
    
    // Assert: Should only return SUCC-001 (mature)
    EXPECT_GE(ready.size(), 1);
    EXPECT_TRUE(std::find(ready.begin(), ready.end(), "SUCC-001") != ready.end());
    
    // CACT-001 should NOT be in list (it's seedling)
    EXPECT_TRUE(std::find(ready.begin(), ready.end(), "CACT-001") == ready.end());
}

/**
 * @test Check available for purchase - mature plant returns true
 */
TEST_F(StaffFacadeTest, IsAvailableForPurchase_MaturePlant_ReturnsTrue) 
{
    // Act
    bool available = facade->isAvailableForPurchase("SUCC-001");
    
    // Assert
    EXPECT_TRUE(available);
}

/**
 * @test Check available for purchase - seedling returns false
 */
TEST_F(StaffFacadeTest, IsAvailableForPurchase_SeedlingPlant_ReturnsFalse) 
{
    // Arrange: Add seedling plant
    DummyPlantFlyweight* cactus = catalog->getBySKU("CACT-001");
    inv->addPlant("CACT-001", new DummyPlant("CACT-001", cactus, new DummySeedlingState()));
    
    // Act
    bool available = facade->isAvailableForPurchase("CACT-001");
    
    // Assert
    EXPECT_FALSE(available);
}

/**
 * @test Validate stock with sufficient quantity returns AVAILABLE
 */
TEST_F(StaffFacadeTest, ValidateStock_SufficientQuantity_ReturnsAvailable) 
{
    // Act
    std::string status = facade->validateStock("SUCC-001", 10);
    
    // Assert
    EXPECT_EQ(status, "AVAILABLE");
}

/**
 * @test Validate stock with partial quantity returns PARTIAL
 */
TEST_F(StaffFacadeTest, ValidateStock_PartialQuantity_ReturnsPartial) 
{
    // Act: Request more than available (15 in stock, need 20)
    std::string status = facade->validateStock("SUCC-001", 20);
    
    // Assert
    EXPECT_EQ(status, "PARTIAL");
}

/**
 * @test Validate stock with no stock returns UNAVAILABLE
 */
TEST_F(StaffFacadeTest, ValidateStock_NoStock_ReturnsUnavailable) 
{
    // Arrange: Deplete stock
    while (inv->available("SUCC-001") > 0) 
    {
        inv->consume("SUCC-001", 1);
    }
    
    // Act
    std::string status = facade->validateStock("SUCC-001", 1);
    
    // Assert
    EXPECT_EQ(status, "UNAVAILABLE");
}

/**
 * @test Validate stock with invalid SKU returns INVALID_SKU
 */
TEST_F(StaffFacadeTest, ValidateStock_InvalidSKU_ReturnsInvalidSKU) 
{
    // Act
    std::string status = facade->validateStock("INVALID-999", 10);
    
    // Assert
    EXPECT_EQ(status, "INVALID_SKU");
}

/**
 * @test Inventory summary contains expected information
 */
TEST_F(StaffFacadeTest, GetInventorySummary_ContainsExpectedInfo) 
{
    // Act
    std::string summary = facade->getInventorySummary();
    
    // Assert
    EXPECT_FALSE(summary.empty());
    EXPECT_TRUE(summary.find("Total SKUs") != std::string::npos);
    EXPECT_TRUE(summary.find("Ready for Sale") != std::string::npos);
    EXPECT_TRUE(summary.find("Low Stock") != std::string::npos);
    EXPECT_TRUE(summary.find("Out of Stock") != std::string::npos);
}

//running all in the main

int main(int argc, char **argv) 
{
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);
    
    // Run all tests
    return RUN_ALL_TESTS();
}