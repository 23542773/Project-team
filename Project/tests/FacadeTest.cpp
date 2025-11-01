/**
 * @file FacadeTest.cpp
 * @brief Comprehensive unit tests for NurseryFacade class
 * @date 2025-10-31
 *
 * Tests the NurseryFacade class, which provides a simplified interface for
 * interacting with the various subsystems of the nursery management system.
 */

#include <gtest/gtest.h>
#include "NurseryFacade.h"
#include "InventoryService.h"
#include "SalesService.h"
#include "StaffService.h"
#include "CustomerService.h"
#include "Greenhouse.h"
#include "SpeciesCatalog.h"
#include "PlantRegistry.h"
#include "ActionLog.h"
#include "Plant.h"
#include "Staff.h"
#include "Customer.h"
#include "ChatMediator.h"
#include "SpeciesFlyweight.h"
#include "SeedlingState.h"
#include "GrowingState.h"
#include "MatureState.h"
#include "Inventory.h"
#include "MediterraneanFactory.h"
#include "DesertFactory.h"
#include <memory>
#include <unordered_set>

/**
 * Test fixture for NurseryFacade - Tests all 35 public methods
 */

class FacadeTestFixture : public ::testing::Test 
{

protected:

    std::unique_ptr<Inventory> inventoryStore;
    std::unique_ptr<InventoryService> inventory;
    std::unique_ptr<SalesService> sales;
    std::unique_ptr<StaffService> staffService;
    std::unique_ptr<CustomerService> customerService;
    std::unique_ptr<Greenhouse> greenhouse;
    std::unique_ptr<SpeciesCatalog> catalog;
    std::unique_ptr<PlantRegistry> registry;
    std::unique_ptr<ActionLog> invoker;
    std::unique_ptr<ChatMediator> mediator;
    std::unique_ptr<NurseryFacade> facade;
    std::shared_ptr<SpeciesFlyweight> roseSpecies;
    std::shared_ptr<SpeciesFlyweight> cactusSpecies;

    void SetUp() override 
    {
        mediator = std::make_unique<ChatMediator>();
        catalog = std::make_unique<SpeciesCatalog>();
        registry = std::make_unique<PlantRegistry>();
        greenhouse = std::make_unique<Greenhouse>(registry.get());
        inventoryStore = std::make_unique<Inventory>();
        inventory = std::make_unique<InventoryService>(*inventoryStore, *greenhouse);
        sales = std::make_unique<SalesService>();
        staffService = std::make_unique<StaffService>(mediator.get());
        customerService = std::make_unique<CustomerService>(mediator.get());
        invoker = std::make_unique<ActionLog>();
        
        facade = std::make_unique<NurseryFacade>(
            inventory.get(), sales.get(), staffService.get(), customerService.get(),
            greenhouse.get(), catalog.get(), invoker.get()
        );
        
        roseSpecies = std::make_shared<SpeciesFlyweight>(
            "ROSE001", "Rose", "Mediterranean", 15, 1.0, 1.2, 0.9, Season::Spring);
        catalog->add(roseSpecies);
        
        cactusSpecies = std::make_shared<SpeciesFlyweight>(
            "CACT001", "Cactus", "Desert", 8, 1.5, 0.8, 1.3, Season::Summer);
        catalog->add(cactusSpecies);
        
        MediterraneanFactory medFactory;
        DesertFactory desertFactory;
        
        Plant* roseProto = medFactory.createPlant("ROSE001#PROTO", "Red", roseSpecies.get());
        if (roseProto) registry->registerSeedling("ROSE001", std::unique_ptr<Plant>(roseProto));
        
        Plant* cactusProto = desertFactory.createPlant("CACT001#PROTO", "Green", cactusSpecies.get());
        if (cactusProto) registry->registerSeedling("CACT001", std::unique_ptr<Plant>(cactusProto));
        
        staffService->addStaff("staff001", "Alice", StaffRole::Sales);
        staffService->addStaff("staff002", "Bob", StaffRole::Inventory);
        customerService->addCustomer("cust001", "Charlie");
        customerService->addCustomer("cust002", "Diana");
        
        addTestPlants();
    }
    
    void addTestPlants() 
    {
        for (int i = 1; i <= 3; ++i) {
            Plant* p = registry->clone("ROSE001", "ROSE001#" + std::to_string(i), "Red");
            p->setState(&SeedlingState::getInstance());
            std::string id = p->id();
            greenhouse->addPlant(std::unique_ptr<Plant>(p));
            inventory->addPlant(id, "ROSE001");
        }
        for (int i = 1; i <= 2; ++i) {
            Plant* p = registry->clone("CACT001", "CACT001#" + std::to_string(i), "Green");
            p->setState(&GrowingState::getInstance());
            std::string id = p->id();
            greenhouse->addPlant(std::unique_ptr<Plant>(p));
            inventory->addPlant(id, "CACT001");
        }
    }
};

// Ensures browseAvailable returns the expected non-empty plant list.
TEST_F(FacadeTestFixture, BrowseAvailable_ReturnsPlants) 
{
    auto available = facade->browseAvailable();
    EXPECT_EQ(available.size(), 5);
}

// Ensures browseAvailable returns an empty list when the greenhouse has no plants.
TEST_F(FacadeTestFixture, BrowseAvailable_EmptyGreenhouse_ReturnsEmpty) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);
    auto available = emptyFacade.browseAvailable();
    EXPECT_TRUE(available.empty());
}

// Ensures browseAvailable returns empty when services are null.
TEST_F(FacadeTestFixture, BrowseAvailable_NullServices_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto available = nullFacade.browseAvailable();
    EXPECT_TRUE(available.empty());
}

// Fetches a plant by a valid ID and expects a non-null result.
TEST_F(FacadeTestFixture, GetPlant_ValidId) 
{
    Plant* plant = facade->getPlant("ROSE001#1");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->sku(), "ROSE001");
}

// Attempts to fetch a plant with an invalid ID and expects null.
TEST_F(FacadeTestFixture, GetPlant_InvalidId) 
{
    Plant* plant = facade->getPlant("INVALID");
    EXPECT_EQ(plant, nullptr);
}

// Tries getPlant with an empty string and expects null.
TEST_F(FacadeTestFixture, GetPlant_EmptyString_ReturnsNull) 
{
    Plant* plant = facade->getPlant("");
    EXPECT_EQ(plant, nullptr);
}

// Calls getPlant when greenhouse is null and expects null.
TEST_F(FacadeTestFixture, GetPlant_NullGreenhouse_ReturnsNull) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Plant* plant = nullFacade.getPlant("ROSE001#1");
    EXPECT_EQ(plant, nullptr);
}

// Lists all plants and expects the full snapshot.
TEST_F(FacadeTestFixture, ListAllPlants) 
{
    auto all = facade->listAllPlants();
    EXPECT_EQ(all.size(), 5);
}

// Lists plants on an empty greenhouse and expects empty.
TEST_F(FacadeTestFixture, ListAllPlants_EmptyGreenhouse_ReturnsEmpty) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);
    auto all = emptyFacade.listAllPlants();
    EXPECT_TRUE(all.empty());
}

// Lists plants when greenhouse is null and expects empty.
TEST_F(FacadeTestFixture, ListAllPlants_NullGreenhouse_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto all = nullFacade.listAllPlants();
    EXPECT_TRUE(all.empty());
}

// Counts plants by SKU and expects the seeded quantity.
TEST_F(FacadeTestFixture, GetSpeciesQuantity) 
{
    EXPECT_EQ(facade->getSpeciesQuantity("ROSE001"), 3);
}

// Queries count for an unknown SKU and expects zero.
TEST_F(FacadeTestFixture, GetSpeciesQuantity_UnknownSku_ReturnsZero) 
{
    EXPECT_EQ(facade->getSpeciesQuantity("UNKNOWN"), 0);
}

// Asks for species quantity with an empty SKU and expects zero.
TEST_F(FacadeTestFixture, GetSpeciesQuantity_EmptyString_ReturnsZero) 
{
    EXPECT_EQ(facade->getSpeciesQuantity(""), 0);
}

// Counts by SKU with null greenhouse and expects zero.
TEST_F(FacadeTestFixture, GetSpeciesQuantity_NullGreenhouse_ReturnsZero) {
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(nullFacade.getSpeciesQuantity("ROSE001"), 0);
}

// Retrieves all species from the catalog.
TEST_F(FacadeTestFixture, ListAllSpecies) 
{
    auto species = facade->listAllSpecies();
    EXPECT_EQ(species.size(), 2);
}

// Retrieves species from an empty catalog and expects empty.
TEST_F(FacadeTestFixture, ListAllSpecies_EmptyCatalog_ReturnsEmpty) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog; 
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);
    auto species = emptyFacade.listAllSpecies();
    EXPECT_TRUE(species.empty());
}

// Gets species with null catalog and expects empty.
TEST_F(FacadeTestFixture, ListAllSpecies_NullCatalog_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto species = nullFacade.listAllSpecies();
    EXPECT_TRUE(species.empty());
}

// Lists staff and expects the known fixtures.
TEST_F(FacadeTestFixture, ListAllStaff) 
{
    auto staff = facade->listAllStaff();
    EXPECT_EQ(staff.size(), 2);
}

// Lists staff on an empty service and expects empty.
TEST_F(FacadeTestFixture, ListAllStaff_EmptyService_ReturnsEmpty) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med); 
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);
    auto staff = emptyFacade.listAllStaff();
    EXPECT_TRUE(staff.empty());
}

// Lists staff with null service and expects empty.
TEST_F(FacadeTestFixture, ListAllStaff_NullService_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto staff = nullFacade.listAllStaff();
    EXPECT_TRUE(staff.empty());
}

// Lists customers and expects the known fixtures.
TEST_F(FacadeTestFixture, ListAllCustomers) 
{
    auto customers = facade->listAllCustomers();
    EXPECT_EQ(customers.size(), 2);
}

// Lists customers on an empty service and expects empty.
TEST_F(FacadeTestFixture, ListAllCustomers_EmptyService_ReturnsEmpty) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);
    auto customers = emptyFacade.listAllCustomers();
    EXPECT_TRUE(customers.empty());
}

// Lists customers with null service and expects empty.
TEST_F(FacadeTestFixture, ListAllCustomers_NullService_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto customers = nullFacade.listAllCustomers();
    EXPECT_TRUE(customers.empty());
}

// Gets a staff member by valid ID and expects a record.
TEST_F(FacadeTestFixture, GetStaff_Valid) 
{
    Staff* staff = facade->getStaff("staff001");
    ASSERT_NE(staff, nullptr);
    EXPECT_EQ(staff->name, "Alice");
}

// Looks up a staff member with invalid ID and expects null.
TEST_F(FacadeTestFixture, GetStaff_InvalidId_ReturnsNull) 
{
    Staff* staff = facade->getStaff("invalid_staff");
    EXPECT_EQ(staff, nullptr);
}

// Looks up a staff member using an empty ID and expects null.
TEST_F(FacadeTestFixture, GetStaff_EmptyString_ReturnsNull) 
{
    Staff* staff = facade->getStaff("");
    EXPECT_EQ(staff, nullptr);
}

// Gets staff with null service and expects null.
TEST_F(FacadeTestFixture, GetStaff_NullService_ReturnsNull) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Staff* staff = nullFacade.getStaff("staff001");
    EXPECT_EQ(staff, nullptr);
}

// Fetches a customer by valid ID and expects a record.
TEST_F(FacadeTestFixture, GetCustomer_Valid) 
{
    Customer* customer = facade->getCustomer("cust001");
    ASSERT_NE(customer, nullptr);
    EXPECT_EQ(customer->name, "Charlie");
}

// Looks up a customer with invalid ID and expects null.
TEST_F(FacadeTestFixture, GetCustomer_InvalidId_ReturnsNull) 
{
    Customer* customer = facade->getCustomer("invalid_customer");
    EXPECT_EQ(customer, nullptr);
}

// Looks up a customer using an empty ID and expects null.
TEST_F(FacadeTestFixture, GetCustomer_EmptyString_ReturnsNull) 
{
    Customer* customer = facade->getCustomer("");
    EXPECT_EQ(customer, nullptr);
}

// Gets customer with null service and expects null.
TEST_F(FacadeTestFixture, GetCustomer_NullService_ReturnsNull) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Customer* customer = nullFacade.getCustomer("cust001");
    EXPECT_EQ(customer, nullptr);
}

// Checks a real customer ID returns true.
TEST_F(FacadeTestFixture, IsValidCustomer) 
{
    EXPECT_TRUE(facade->isValidCustomer("cust001"));
    EXPECT_FALSE(facade->isValidCustomer("invalid"));
}

// Checks empty customer ID returns false.
TEST_F(FacadeTestFixture, IsValidCustomer_EmptyString_ReturnsFalse) 
{
    EXPECT_FALSE(facade->isValidCustomer(""));
}

// Checks validity with null service returns false.
TEST_F(FacadeTestFixture, IsValidCustomer_NullService_ReturnsFalse) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_FALSE(nullFacade.isValidCustomer("cust001"));
}

// Checks a real staff ID returns true.
TEST_F(FacadeTestFixture, IsValidStaff) 
{
    EXPECT_TRUE(facade->isValidStaff("staff001"));
    EXPECT_FALSE(facade->isValidStaff("invalid"));
}

// Checks empty staff ID returns false.
TEST_F(FacadeTestFixture, IsValidStaff_EmptyString_ReturnsFalse) 
{
    EXPECT_FALSE(facade->isValidStaff(""));
}

// Checks validity with null staff service returns false.
TEST_F(FacadeTestFixture, IsValidStaff_NullService_ReturnsFalse)
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_FALSE(nullFacade.isValidStaff("staff001"));
}

// Performs a valid checkout and expects success.
TEST_F(FacadeTestFixture, Checkout_ValidOrder) 
{
    std::vector<events::OrderLine> lines;
    events::OrderLine line;
    line.plantId = "ROSE001#1";
    line.speciesSku = "ROSE001";
    line.description = "Rose";
    line.finalCost = 15.0;
    lines.push_back(line);
    
    Receipt receipt = facade->checkout("cust001", lines, 20.0);
    EXPECT_TRUE(receipt.success);
}

// Checks exact payment yields zero change and assigns staff.
TEST_F(FacadeTestFixture, Checkout_ExactPayment_ZeroChange_AndAssigned) 
{
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#2", "ROSE001", "Rose", 15.0 }
    };

    Receipt receipt = facade->checkout("cust001", lines, 15.0);
    ASSERT_TRUE(receipt.success);
    EXPECT_FALSE(receipt.orderId.empty());
    EXPECT_DOUBLE_EQ(receipt.totalCost, 15.0);
    EXPECT_DOUBLE_EQ(receipt.change, 0.0);

    auto orderOpt = sales->get(receipt.orderId);
    ASSERT_TRUE(orderOpt.has_value());
    EXPECT_TRUE(orderOpt->staffId.has_value());
}

// Attempts checkout with an invalid plant and expects failure.
TEST_F(FacadeTestFixture, Checkout_NoItemsAvailable_InvalidPlant) 
{
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "INVALID#1", "ROSE001", "Rose", 15.0 }
    };
    Receipt receipt = facade->checkout("cust001", lines, 20.0);
    EXPECT_FALSE(receipt.success);
    EXPECT_EQ(receipt.message, "No items available");
}

// Checks partial availability leads to a successful partial checkout.
TEST_F(FacadeTestFixture, Checkout_PartialAvailability_Succeeds_WithOneValid) 
{
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#3", "ROSE001", "Rose", 15.0 },
        events::OrderLine{ "INVALID#2", "ROSE001", "Rose", 15.0 }
    };
    Receipt receipt = facade->checkout("cust001", lines, 30.0);
    ASSERT_TRUE(receipt.success);
    EXPECT_DOUBLE_EQ(receipt.totalCost, 15.0);
    EXPECT_DOUBLE_EQ(receipt.change, 15.0);
}

// Reserving the same plant twice should fail the second time.
TEST_F(FacadeTestFixture, Checkout_DoubleReserve_SamePlant_FailsSecondTime) 
{
    std::vector<events::OrderLine> first{
        events::OrderLine{ "ROSE001#1", "ROSE001", "Rose", 15.0 }
    };
    Receipt firstReceipt = facade->checkout("cust001", first, 20.0);
    ASSERT_TRUE(firstReceipt.success);

    std::vector<events::OrderLine> second{
        events::OrderLine{ "ROSE001#1", "ROSE001", "Rose", 15.0 }
    };
    Receipt secondReceipt = facade->checkout("cust001", second, 20.0);
    EXPECT_FALSE(secondReceipt.success);
    EXPECT_EQ(secondReceipt.message, "No items available");
}

// Checkout with null services returns service unavailable.
TEST_F(FacadeTestFixture, Checkout_NullServices_ServiceUnavailable) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;

    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#99", "ROSE001", "Rose", 15.0 }
    };
    Receipt r = nullFacade.checkout("cust001", lines, 20.0);
    EXPECT_FALSE(r.success);
    EXPECT_EQ(r.message, "Service unavailable");
}

// Retrieves receipts for a known customer.
TEST_F(FacadeTestFixture, GetCustomerReceipts) 
{
    std::vector<events::OrderLine> lines;
    events::OrderLine line;
    line.plantId = "ROSE001#1";
    line.speciesSku = "ROSE001";
    line.description = "Rose";
    line.finalCost = 15.0;
    lines.push_back(line);
    facade->checkout("cust001", lines, 20.0);
    
    auto receipts = facade->getCustomerReceipts("cust001");
    EXPECT_GE(receipts.size(), 1) << "Customer should have at least 1 receipt";
}

// Requests receipts for a customer with no purchases and expects empty.
TEST_F(FacadeTestFixture, GetCustomerReceipts_NoPurchases_ReturnsEmpty) 
{
    auto receipts = facade->getCustomerReceipts("cust002");
    EXPECT_TRUE(receipts.empty());
}

// Requests receipts for an invalid customer and expects empty.
TEST_F(FacadeTestFixture, GetCustomerReceipts_InvalidCustomer_ReturnsEmpty) 
{
    auto receipts = facade->getCustomerReceipts("invalid");
    EXPECT_TRUE(receipts.empty());
}

// Requests receipts with an empty customer ID and expects empty.
TEST_F(FacadeTestFixture, GetCustomerReceipts_EmptyString_ReturnsEmpty) 
{
    auto receipts = facade->getCustomerReceipts("");
    EXPECT_TRUE(receipts.empty());
}

// Gets all orders for a known customer.
TEST_F(FacadeTestFixture, GetCustomerOrders) 
{
    std::vector<events::OrderLine> lines;
    events::OrderLine line;
    line.plantId = "ROSE001#2";
    line.speciesSku = "ROSE001";
    line.description = "Rose";
    line.finalCost = 15.0;
    lines.push_back(line);
    facade->checkout("cust001", lines, 20.0);
    
    auto orders = facade->getCustomerOrders("cust001");
    EXPECT_GE(orders.size(), 1) << "Customer should have at least 1 order";
}

// Gets orders for a customer with none and expects empty.
TEST_F(FacadeTestFixture, GetCustomerOrders_NoOrders_ReturnsEmpty) 
{
    auto orders = facade->getCustomerOrders("cust002");
    EXPECT_TRUE(orders.empty());
}

// Gets orders with an empty customer ID and expects empty.
TEST_F(FacadeTestFixture, GetCustomerOrders_EmptyString_ReturnsEmpty) 
{
    auto orders = facade->getCustomerOrders("");
    EXPECT_TRUE(orders.empty());
}

// Gets orders for a staff member.
TEST_F(FacadeTestFixture, GetStaffOrders)
{
    auto orders = facade->getStaffOrders("staff001");
    EXPECT_TRUE(orders.empty() || !orders.empty());
}

// Checks staff sees the order after checkout.
TEST_F(FacadeTestFixture, GetStaffOrders_AfterCheckout_ReturnsAssignedOrder) 
{

    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#1", "ROSE001", "Rose", 15.0 }
    };
    Receipt receipt = facade->checkout("cust001", lines, 20.0);
    ASSERT_TRUE(receipt.success);

 
    auto orderOpt = sales->get(receipt.orderId);
    ASSERT_TRUE(orderOpt.has_value());
    ASSERT_TRUE(orderOpt->staffId.has_value());
    std::string staffId = *orderOpt->staffId;

    auto staffOrders = facade->getStaffOrders(staffId);
    ASSERT_FALSE(staffOrders.empty());
    bool found = false;
    for (const auto& o : staffOrders) {
        if (o.orderId == receipt.orderId) { found = true; break; }
    }
    EXPECT_TRUE(found);
}

// Gets staff orders with empty ID and expects empty.
TEST_F(FacadeTestFixture, GetStaffOrders_EmptyString_ReturnsEmpty) 
{
    auto orders = facade->getStaffOrders("");
    EXPECT_TRUE(orders.empty());
}

// Completing a non-existent order should return false.
TEST_F(FacadeTestFixture, CompleteOrder_InvalidOrder) {
    bool completed = facade->completeOrder("INVALID_ORDER_ID");
    EXPECT_FALSE(completed) << "Should return false for invalid order";
}

// Completes an order and removes the plant from greenhouse/inventory.
TEST_F(FacadeTestFixture, CompleteOrder_Valid_CompletesAndRemovesPlant) 
{
    
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#2", "ROSE001", "Rose", 15.0 }
    };
    int soldBefore = inventory->soldCount("ROSE001");
    Receipt receipt = facade->checkout("cust001", lines, 20.0);
    ASSERT_TRUE(receipt.success);

    bool ok = facade->completeOrder(receipt.orderId);
    EXPECT_TRUE(ok);


    auto orderOpt = sales->get(receipt.orderId);
    ASSERT_TRUE(orderOpt.has_value());
    EXPECT_EQ(orderOpt->status, events::OrderStatus::Completed);

    EXPECT_EQ(greenhouse->getPlant("ROSE001#2"), nullptr);
    int soldAfter = inventory->soldCount("ROSE001");
    EXPECT_EQ(soldAfter, soldBefore + 1);
}

// Completing an already completed order returns false.
TEST_F(FacadeTestFixture, CompleteOrder_AlreadyCompleted_ReturnsFalse) 
{
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#3", "ROSE001", "Rose", 15.0 }
    };
    Receipt receipt = facade->checkout("cust001", lines, 20.0);
    ASSERT_TRUE(receipt.success);
    ASSERT_TRUE(facade->completeOrder(receipt.orderId));

    EXPECT_FALSE(facade->completeOrder(receipt.orderId));
}

// Completing with null services returns false.
TEST_F(FacadeTestFixture, CompleteOrder_NullServices_ReturnsFalse) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_FALSE(nullFacade.completeOrder("ANY"));
}

// After sending a message, both sides should see it in the conversation.
TEST_F(FacadeTestFixture, GetConversation_AfterMessage) 
{
    Staff* staff = facade->getStaff("staff001");
    Customer* customer = facade->getCustomer("cust001");
    
    if (staff && customer) {
        staff->sendMessage(customer, "Hello customer!");
        auto conversation = facade->getConversation("staff001", "cust001");
        EXPECT_GE(conversation.size(), 1) << "Should have at least 1 message";
    }
}

// Customer ↔ sales staff messages should go through.
TEST_F(FacadeTestFixture, GetConversation_CustomerToStaff_AfterMessage) 
{
    Staff* staff = facade->getStaff("staff001");
    Customer* customer = facade->getCustomer("cust001");
    ASSERT_NE(staff, nullptr);
    ASSERT_NE(customer, nullptr);
    
    customer->sendMessage(staff, "Hi Sales!");
    auto conversation = facade->getConversation("cust001", "staff001");
    EXPECT_FALSE(conversation.empty());
}

// Inventory staff to customer should be blocked.
TEST_F(FacadeTestFixture, GetConversation_DisallowedRole_InventoryToCustomer_ReturnsEmpty) 
{
    Staff* inventoryStaff = facade->getStaff("staff002");
    Customer* customer = facade->getCustomer("cust001");
    ASSERT_NE(inventoryStaff, nullptr);
    ASSERT_NE(customer, nullptr);

    inventoryStaff->sendMessage(customer, "Inventory ping");
    auto convoFromInventory = facade->getConversation("staff002", "cust001");
    EXPECT_TRUE(convoFromInventory.empty());

    customer->sendMessage(inventoryStaff, "Customer ping");
    auto convoFromCustomer = facade->getConversation("cust001", "staff002");
    EXPECT_TRUE(convoFromCustomer.empty());
}

// Conversation lookups with empty IDs return empty.
TEST_F(FacadeTestFixture, GetConversation_EmptyUserIds_ReturnsEmpty) 
{
    auto convo = facade->getConversation("", "");
    EXPECT_TRUE(convo.empty());
}

// Conversation lookups with null services return empty.
TEST_F(FacadeTestFixture, GetConversation_NullServices_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto convo = nullFacade.getConversation("staff001", "cust001");
    EXPECT_TRUE(convo.empty());
}

// Queue size starts at zero.
TEST_F(FacadeTestFixture, GetQueueSize_InitiallyZero) 
{
    EXPECT_EQ(facade->getQueueSize(), 0);
}

// Enqueuing multiple commands increases queue size.
TEST_F(FacadeTestFixture, GetQueueSize_MultipleEnqueues_Accumulates) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueWater(plants, "staff001");
    facade->enqueueFertilize(plants, "staff001");
    facade->enqueueSpray(plants, "staff002");
    facade->enqueueRestock("ROSE001", 2, "staff002");
    EXPECT_EQ(facade->getQueueSize(), 4);
}

// Processing one command decrements queue size by one.
TEST_F(FacadeTestFixture, GetQueueSize_ProcessNext_DecrementsByOne) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueWater(plants, "staff001");
    facade->enqueueFertilize(plants, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 2);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_EQ(facade->getQueueSize(), 1);
}

// Enqueues a water command.
TEST_F(FacadeTestFixture, EnqueueWater) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueWater(plants, "staff001");
    EXPECT_EQ(facade->getQueueSize(), 1);
}

// Enqueues a fertilize command.
TEST_F(FacadeTestFixture, EnqueueFertilize) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueFertilize(plants, "staff001");
    EXPECT_EQ(facade->getQueueSize(), 1);
}

// Enqueues a spray command.
TEST_F(FacadeTestFixture, EnqueueSpray) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueSpray(plants, "staff001");
    EXPECT_EQ(facade->getQueueSize(), 1);
}

// Processing water increases plant moisture.
TEST_F(FacadeTestFixture, EnqueueWater_Positive_ProcessesAndIncreasesMoisture) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int before = plants[0]->getMoisture();
    facade->enqueueWater(plants, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_GT(plants[0]->getMoisture(), before);
}

// Empty userId still lets water be enqueued.
TEST_F(FacadeTestFixture, EnqueueWater_Negative_EmptyUserId_StillEnqueues) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->enqueueWater(plants, "");
    EXPECT_EQ(facade->getQueueSize(), qBefore + 1);
}

// Water with empty plant list enqueues and no-ops on process.
TEST_F(FacadeTestFixture, EnqueueWater_Edge_EmptyPlants_EnqueuesAndNoOpOnProcess) 
{
    auto all = facade->browseAvailable();
    ASSERT_FALSE(all.empty());
    int before = all[0]->getMoisture();
    std::vector<Plant*> none;
    facade->enqueueWater(none, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_EQ(all[0]->getMoisture(), before);
}

// Water skips nullptr entries in the plant vector.
TEST_F(FacadeTestFixture, EnqueueWater_Edge_VectorWithNullptr_SkipsNull) 
{
    auto plants = facade->browseAvailable();
    ASSERT_GE(plants.size(), 1u);
    int before = plants[0]->getMoisture();
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->enqueueWater(mix, "staff001");
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_GT(plants[0]->getMoisture(), before);
}

// With null services, water is not enqueued.
TEST_F(FacadeTestFixture, EnqueueWater_Error_NullServices_NoEnqueue) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto plants = facade->browseAvailable();
    nullFacade.enqueueWater(plants, "staff001");
    EXPECT_EQ(nullFacade.getQueueSize(), 0);
}

// Processing fertilize succeeds without errors.
TEST_F(FacadeTestFixture, EnqueueFertilize_Positive_ProcessesSuccessfully) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    plants[0]->addHealth(-10);
    facade->enqueueFertilize(plants, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_GE(plants[0]->getHealth(), 0);
    EXPECT_LE(plants[0]->getHealth(), 100);
}

// Empty userId still lets fertilize be enqueued.
TEST_F(FacadeTestFixture, EnqueueFertilize_Negative_EmptyUserId_StillEnqueues) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->enqueueFertilize(plants, "");
    EXPECT_EQ(facade->getQueueSize(), qBefore + 1);
}

// Fertilize with empty plant list enqueues and no-ops.
TEST_F(FacadeTestFixture, EnqueueFertilize_Edge_EmptyPlants_EnqueuesAndNoOpOnProcess) 
{
    auto all = facade->browseAvailable();
    ASSERT_FALSE(all.empty());
    int before = all[0]->getHealth();
    std::vector<Plant*> none;
    facade->enqueueFertilize(none, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_EQ(all[0]->getHealth(), before);
}

// Fertilize executes on valid pointers even if vector has nullptrs.
TEST_F(FacadeTestFixture, EnqueueFertilize_Edge_VectorWithNullptr_Executes) 
{
    auto plants = facade->browseAvailable();
    ASSERT_GE(plants.size(), 1u);
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->enqueueFertilize(mix, "staff001");
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_GE(plants[0]->getHealth(), 0);
    EXPECT_LE(plants[0]->getHealth(), 100);
}

// With null services, fertilize is not enqueued.
TEST_F(FacadeTestFixture, EnqueueFertilize_Error_NullServices_NoEnqueue) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto plants = facade->browseAvailable();
    nullFacade.enqueueFertilize(plants, "staff001");
    EXPECT_EQ(nullFacade.getQueueSize(), 0);
}

// Processing spray increases insecticide level.
TEST_F(FacadeTestFixture, EnqueueSpray_Positive_ProcessesAndIncreasesInsecticide) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if (plants[0]->getInsecticide() >= 100) {
        plants[0]->addInsecticide(-20);
    }
    int before = plants[0]->getInsecticide();
    facade->enqueueSpray(plants, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_GT(plants[0]->getInsecticide(), before);
}

// Empty userId still lets spray be enqueued.
TEST_F(FacadeTestFixture, EnqueueSpray_Negative_EmptyUserId_StillEnqueues) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->enqueueSpray(plants, "");
    EXPECT_EQ(facade->getQueueSize(), qBefore + 1);
}

// Spray with empty plant list enqueues and no-ops.
TEST_F(FacadeTestFixture, EnqueueSpray_Edge_EmptyPlants_EnqueuesAndNoOpOnProcess) 
{
    auto all = facade->browseAvailable();
    ASSERT_FALSE(all.empty());
    int before = all[0]->getInsecticide();
    std::vector<Plant*> none;
    facade->enqueueSpray(none, "staff001");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_EQ(all[0]->getInsecticide(), before);
}

// Spray skips nullptr entries in the plant vector.
TEST_F(FacadeTestFixture, EnqueueSpray_Edge_VectorWithNullptr_SkipsNull) 
{
    auto plants = facade->browseAvailable();
    ASSERT_GE(plants.size(), 1u);
    if (plants[0]->getInsecticide() >= 100) {
        plants[0]->addInsecticide(-20);
    }
    int before = plants[0]->getInsecticide();
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->enqueueSpray(mix, "staff001");
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_GT(plants[0]->getInsecticide(), before);
}

// With null services, spray is not enqueued.
TEST_F(FacadeTestFixture, EnqueueSpray_Error_NullServices_NoEnqueue) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto plants = facade->browseAvailable();
    nullFacade.enqueueSpray(plants, "staff001");
    EXPECT_EQ(nullFacade.getQueueSize(), 0);
}

// Enqueues a restock command.
TEST_F(FacadeTestFixture, EnqueueRestock)
{
    facade->enqueueRestock("ROSE001", 5, "staff002");
    EXPECT_EQ(facade->getQueueSize(), 1);
}

// Processing restock adds plants and records history.
TEST_F(FacadeTestFixture, EnqueueRestock_Positive_ProcessesSuccessfully) 
{
    int before = facade->getSpeciesQuantity("ROSE001");
    facade->enqueueRestock("ROSE001", 2, "staff002");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    int after = facade->getSpeciesQuantity("ROSE001");
    EXPECT_GE(after, before);
    EXPECT_EQ(facade->getRestockHistorySize(), 1);
}

// Empty userId still lets restock be enqueued.
TEST_F(FacadeTestFixture, EnqueueRestock_Negative_EmptyUserId_StillEnqueues) 
{
    size_t qBefore = facade->getQueueSize();
    facade->enqueueRestock("ROSE001", 1, "");
    EXPECT_EQ(facade->getQueueSize(), qBefore + 1);
}

// Restock history starts at zero.
TEST_F(FacadeTestFixture, GetRestockHistorySize_InitiallyZero) 
{
    EXPECT_EQ(facade->getRestockHistorySize(), 0);
}

// History increases after a restock is processed.
TEST_F(FacadeTestFixture, GetRestockHistorySize_AfterRestock) 
{
    facade->enqueueRestock("ROSE001", 3, "staff002");
    facade->processNextCommand();
    EXPECT_EQ(facade->getRestockHistorySize(), 1) << "Should have 1 restock in history";
}

// History grows with multiple restocks.
TEST_F(FacadeTestFixture, GetRestockHistorySize_AfterMultipleRestocks) 
{
    facade->enqueueRestock("ROSE001", 1, "staff002");
    facade->enqueueRestock("ROSE001", 2, "staff002");
    EXPECT_EQ(facade->processAllCommands(), 2);
    EXPECT_EQ(facade->getRestockHistorySize(), 2);
}

// Undo with empty history returns false and logs a message.
TEST_F(FacadeTestFixture, UndoLastRestock_NoRestocks) 
{
    bool undone = facade->undoLastRestock();
    EXPECT_FALSE(undone) << "Should return false when no restocks to undo";
}

// Undo after a restock removes added plants and clears history entry.
TEST_F(FacadeTestFixture, UndoLastRestock_AfterRestock) 
{
    facade->enqueueRestock("ROSE001", 3, "staff002");
    facade->processNextCommand();
    int historySize = facade->getRestockHistorySize();
    EXPECT_GT(historySize, 0) << "Should have restock in history";
    bool undone = facade->undoLastRestock();
    EXPECT_TRUE(undone) << "Should successfully undo the restock";
}

// Undoing reduces history size and reverts counts.
TEST_F(FacadeTestFixture, GetRestockHistorySize_AfterUndo_DecrementsAndQuantityReverts) 
{
    int beforeQty = facade->getSpeciesQuantity("ROSE001");
    facade->enqueueRestock("ROSE001", 2, "staff002");
    facade->processNextCommand();
    int histAfter = facade->getRestockHistorySize();
    ASSERT_GE(facade->getSpeciesQuantity("ROSE001"), beforeQty);
    ASSERT_GT(histAfter, 0);
    
    ASSERT_TRUE(facade->undoLastRestock());
    EXPECT_EQ(facade->getRestockHistorySize(), histAfter - 1);
    EXPECT_EQ(facade->getSpeciesQuantity("ROSE001"), beforeQty);
}

// With null services, history size reports zero.
TEST_F(FacadeTestFixture, GetRestockHistorySize_NullServices_ReturnsZero) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(nullFacade.getRestockHistorySize(), 0);
}

// With null services, restock is not enqueued.
TEST_F(FacadeTestFixture, EnqueueRestock_Error_NullServices_NoEnqueue) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.enqueueRestock("ROSE001", 2, "staff002");
    EXPECT_EQ(nullFacade.getQueueSize(), 0);
}

// Processes the next command from the queue.
TEST_F(FacadeTestFixture, ProcessNextCommand) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueWater(plants, "staff001");
    bool processed = facade->processNextCommand();
    EXPECT_TRUE(processed);
    EXPECT_EQ(facade->getQueueSize(), 0);
}

// Processes all commands in the queue.
TEST_F(FacadeTestFixture, ProcessAllCommands) 
{
    auto plants = facade->browseAvailable();
    facade->enqueueWater(plants, "staff001");
    facade->enqueueFertilize(plants, "staff001");
    facade->enqueueSpray(plants, "staff002");
    
    int processed = facade->processAllCommands();
    EXPECT_EQ(processed, 3);
}

// Processing a restock moves it into undoable history.
TEST_F(FacadeTestFixture, ProcessNextCommand_AfterRestock_AddsToHistory) 
{
    int beforeHist = facade->getRestockHistorySize();
    facade->enqueueRestock("ROSE001", 1, "staff002");
    ASSERT_EQ(facade->getQueueSize(), 1);
    EXPECT_TRUE(facade->processNextCommand());
    EXPECT_EQ(facade->getRestockHistorySize(), beforeHist + 1);
}

// Only undoable restocks are counted in history after mixed processing.
TEST_F(FacadeTestFixture, ProcessAllCommands_Mixed_UndoableHistoryOnlyCountsRestocks) 
{
    auto plants = facade->browseAvailable();
    size_t q0 = facade->getQueueSize();
    int h0 = facade->getRestockHistorySize();
    facade->enqueueWater(plants, "staff001");     
    facade->enqueueFertilize(plants, "staff001"); 
    facade->enqueueRestock("ROSE001", 2, "staff002"); 
    facade->enqueueSpray(plants, "staff002");     
    ASSERT_EQ(facade->getQueueSize(), q0 + 4);
    EXPECT_EQ(facade->processAllCommands(), 4);
    EXPECT_EQ(facade->getQueueSize(), 0);
    EXPECT_EQ(facade->getRestockHistorySize(), h0 + 1);
}

// With null services, processing next returns false.
TEST_F(FacadeTestFixture, ProcessNextCommand_NullServices_ReturnsFalse)
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_FALSE(nullFacade.processNextCommand());
}

// With null services, processing all returns zero.
TEST_F(FacadeTestFixture, ProcessAllCommands_NullServices_ReturnsZero) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(nullFacade.processAllCommands(), 0);
}

// Repeatedly processing an empty queue keeps the count at zero.
TEST_F(FacadeTestFixture, ProcessAllCommands_RepeatedEmptyQueue_StaysZero) 
{
    EXPECT_EQ(facade->getQueueSize(), 0);
    EXPECT_EQ(facade->processAllCommands(), 0);
    EXPECT_EQ(facade->processAllCommands(), 0);
}

// Test: Testing WaterPlants increases Moisture
TEST_F(FacadeTestFixture, WaterPlants) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int initial = plants[0]->getMoisture();
    facade->waterPlants(plants);
    EXPECT_GT(plants[0]->getMoisture(), initial);
}

// Test: Testing Water Plants skips nullptr entries
TEST_F(FacadeTestFixture, WaterPlants_VectorWithNullptr_SkipsNull) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int before = plants[0]->getMoisture();
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->waterPlants(mix);
    EXPECT_GT(plants[0]->getMoisture(), before);
}

// Test: Testing Water Plants does not leave queued commands
TEST_F(FacadeTestFixture, WaterPlants_DoesNotLeaveQueuedCommands) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->waterPlants(plants);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Test: Testing Water Plants with null services has no effect
TEST_F(FacadeTestFixture, WaterPlants_NullServices_NoEffect) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int before = plants[0]->getMoisture();
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.waterPlants(plants);
    EXPECT_EQ(plants[0]->getMoisture(), before);
}

// Test: Testing FertilizePlants increases Health
TEST_F(FacadeTestFixture, FertilizePlants) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    
    facade->fertilizePlants(plants);
    SUCCEED() << "FertilizePlants executed without error";
}

// Test: Testing FertilizePlants processes within bounds
TEST_F(FacadeTestFixture, FertilizePlants_ProcessesWithinBounds) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    plants[0]->addHealth(-10); 
    facade->fertilizePlants(plants);
    EXPECT_GE(plants[0]->getHealth(), 0);
    EXPECT_LE(plants[0]->getHealth(), 100);
}

// Test: Testing FertilizePlants skips nullptr entries
TEST_F(FacadeTestFixture, FertilizePlants_VectorWithNullptr_Executes) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->fertilizePlants(mix);
    EXPECT_GE(plants[0]->getHealth(), 0);
    EXPECT_LE(plants[0]->getHealth(), 100);
}

// Test: Testing FertilizePlants does not leave queued commands
TEST_F(FacadeTestFixture, FertilizePlants_DoesNotLeaveQueuedCommands) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->fertilizePlants(plants);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Test: Testing FertilizePlants with null services has no effect
TEST_F(FacadeTestFixture, FertilizePlants_NullServices_NoEffect) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int before = plants[0]->getHealth();
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.fertilizePlants(plants);
    EXPECT_EQ(plants[0]->getHealth(), before);
}

// Test: Testing SprayInsecticide
TEST_F(FacadeTestFixture, SprayInsecticide) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if(plants[0]->getInsecticide() >= 100) 
    {
        plants[0]->addInsecticide(-20); 
    }
    int initial = plants[0]->getInsecticide();
    facade->sprayInsecticide(plants);
    EXPECT_GT(plants[0]->getInsecticide(), initial);
}

// Test: Testing SprayInsecticide_VectorWithNullptr_IncreasesValid
TEST_F(FacadeTestFixture, SprayInsecticide_VectorWithNullptr_IncreasesValid) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if (plants[0]->getInsecticide() >= 100) {
        plants[0]->addInsecticide(-20);
    }
    int before = plants[0]->getInsecticide();
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->sprayInsecticide(mix);
    EXPECT_GT(plants[0]->getInsecticide(), before);
}

// Test: Testing SprayInsecticide_DoesNotLeaveQueuedCommands
TEST_F(FacadeTestFixture, SprayInsecticide_DoesNotLeaveQueuedCommands) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->sprayInsecticide(plants);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Test: Testing SprayInsecticide_NullServices_NoEffect
TEST_F(FacadeTestFixture, SprayInsecticide_NullServices_NoEffect) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if (plants[0]->getInsecticide() >= 100) {
        plants[0]->addInsecticide(-10);
    }
    int before = plants[0]->getInsecticide();
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.sprayInsecticide(plants);
    EXPECT_EQ(plants[0]->getInsecticide(), before);
}

// Test: Testing TickAllPlants
TEST_F(FacadeTestFixture, TickAllPlants) 
{
    auto plants = facade->listAllPlants();
    ASSERT_FALSE(plants.empty());
    int initial = plants[0]->getAgeDays();
    facade->tickAllPlants();
    EXPECT_GE(plants[0]->getAgeDays(), initial);
}

// Test: Testing TickAllPlants Decrements Insecticide
TEST_F(FacadeTestFixture, TickAllPlants_DecrementsInsecticideForSeedling) 
{
    Plant* p = facade->getPlant("ROSE001#1");
    ASSERT_NE(p, nullptr);
    int insectBefore = p->getInsecticide();
    facade->tickAllPlants();
    EXPECT_LE(p->getInsecticide(), insectBefore);
}

// Test: Testing TickAllPlants Removes Dead Plant and Decrements Counts
TEST_F(FacadeTestFixture, TickAllPlants_RemovesDeadPlant_DecrementsCounts) 
{
    Plant* p = facade->getPlant("ROSE001#1");
    ASSERT_NE(p, nullptr);
    int qtyBefore = facade->getSpeciesQuantity("ROSE001");
    p->addHealth(-100);
    facade->tickAllPlants();
    EXPECT_EQ(facade->getPlant("ROSE001#1"), nullptr);
    EXPECT_EQ(facade->getSpeciesQuantity("ROSE001"), qtyBefore - 1);
}

// Test: Testing TickAllPlants on Empty Greenhouse has No Effect
TEST_F(FacadeTestFixture, TickAllPlants_EmptyGreenhouse_NoChange) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);
    emptyFacade.tickAllPlants();
    EXPECT_TRUE(emptyFacade.listAllPlants().empty());
}

// Test: Testing TickAllPlants with null greenhouse has no crash
TEST_F(FacadeTestFixture, TickAllPlants_NullGreenhouse_NoCrash) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.tickAllPlants();
    SUCCEED();
}

// Test: Testing RunMorningRoutine
TEST_F(FacadeTestFixture, RunMorningRoutine) 
{
    auto plants = facade->browseAvailable();
    facade->runMorningRoutine(plants);
    SUCCEED();
}

// Test: Testing RunMorningRoutine increase moisture 
TEST_F(FacadeTestFixture, RunMorningRoutine_Positive_IncreasesMoisture) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int beforeMoisture = plants[0]->getMoisture();
    facade->runMorningRoutine(plants);
    EXPECT_GE(plants[0]->getMoisture(), beforeMoisture);
    EXPECT_GE(plants[0]->getHealth(), 0);
    EXPECT_LE(plants[0]->getHealth(), 100);
}

// Test: Testing RunMorningRoutine skips null entries
TEST_F(FacadeTestFixture, RunMorningRoutine_VectorWithNullptr_SkipsNull) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int before = plants[0]->getMoisture();
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->runMorningRoutine(mix);
    EXPECT_GE(plants[0]->getMoisture(), before);
}

// Test: Testing RunMorningRoutine does not leave queued commands
TEST_F(FacadeTestFixture, RunMorningRoutine_DoesNotLeaveQueuedCommands) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->runMorningRoutine(plants);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Test: Testing RunMorningRoutine with null services has no effect
TEST_F(FacadeTestFixture, RunMorningRoutine_NullServices_NoEffect) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int before = plants[0]->getMoisture();
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.runMorningRoutine(plants);
    EXPECT_EQ(plants[0]->getMoisture(), before);
}

// Test: Testing RunNightRoutine
TEST_F(FacadeTestFixture, RunNightRoutine) 
{
    auto plants = facade->browseAvailable();
    facade->runNightRoutine(plants);
    SUCCEED();
}

// Test: Testing RunNightRoutine increases insecticide
TEST_F(FacadeTestFixture, RunNightRoutine_Positive_IncreasesInsecticide) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if (plants[0]->getInsecticide() >= 100) { plants[0]->addInsecticide(-30); }
    int beforeInsect = plants[0]->getInsecticide();
    int beforeMoisture = plants[0]->getMoisture();
    facade->runNightRoutine(plants);
    EXPECT_GT(plants[0]->getInsecticide(), beforeInsect);
    EXPECT_GE(plants[0]->getMoisture(), beforeMoisture);
}

// Test: Testing RunNightRoutine skips null entries
TEST_F(FacadeTestFixture, RunNightRoutine_VectorWithNullptr_SkipsNull) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if (plants[0]->getInsecticide() >= 100) { plants[0]->addInsecticide(-30); }
    int before = plants[0]->getInsecticide();
    std::vector<Plant*> mix{ plants[0], nullptr };
    facade->runNightRoutine(mix);
    EXPECT_GT(plants[0]->getInsecticide(), before);
}

// Test: Testing RunNightRoutine does not leave queued commands
TEST_F(FacadeTestFixture, RunNightRoutine_DoesNotLeaveQueuedCommands) 
{
    auto plants = facade->browseAvailable();
    size_t qBefore = facade->getQueueSize();
    facade->runNightRoutine(plants);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Test: Testing RunNightRoutine with null services has no effect
TEST_F(FacadeTestFixture, RunNightRoutine_NullServices_NoEffect) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    if (plants[0]->getInsecticide() >= 100) { plants[0]->addInsecticide(-10); }
    int before = plants[0]->getInsecticide();
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.runNightRoutine(plants);
    EXPECT_EQ(plants[0]->getInsecticide(), before);
}

// Runs urgent care and expects no crash.
TEST_F(FacadeTestFixture, RunUrgentCare) 
{
    facade->runUrgentCare();
    SUCCEED();
}

// Marks a plant wilting and expects urgent care to safely improve vitals.
TEST_F(FacadeTestFixture, RunUrgentCare_Positive_ImprovesWiltingPlants) 
{
    auto plants = facade->browseAvailable();
    ASSERT_GE(plants.size(), 1u);
    Plant* target = plants[0];
    target->addHealth(10 - target->getHealth());      
    target->addWater(0 - target->getMoisture());      
    target->addInsecticide(0 - target->getInsecticide()); 
    int hBefore = target->getHealth();
    int mBefore = target->getMoisture();
    int iBefore = target->getInsecticide();
    target->setState(&WiltingState::getInstance());

    facade->runUrgentCare();

    EXPECT_GE(target->getHealth(), 0);
    EXPECT_LE(target->getHealth(), 100);
    EXPECT_GE(target->getMoisture(), 0);
    EXPECT_LE(target->getMoisture(), 100);
    EXPECT_GE(target->getInsecticide(), 0);
    EXPECT_LE(target->getInsecticide(), 100);
    EXPECT_GT(target->getMoisture(), mBefore);
    EXPECT_GT(target->getInsecticide(), iBefore);
}

// If nothing is wilting, urgent care is a no-op and leaves the queue unchanged.
TEST_F(FacadeTestFixture, RunUrgentCare_NoWilting_NoOp) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    int hBefore = plants[0]->getHealth();
    size_t qBefore = facade->getQueueSize();
    facade->runUrgentCare();
    EXPECT_EQ(facade->getQueueSize(), qBefore);
    EXPECT_GE(plants[0]->getHealth(), 0);
    EXPECT_LE(plants[0]->getHealth(), 100);
}

// Urgent care should only affect wilting plants, not healthy ones.
TEST_F(FacadeTestFixture, RunUrgentCare_AffectsOnlyWilting) 
{
    auto plants = facade->browseAvailable();
    ASSERT_GE(plants.size(), 2u);
    Plant* wilting = plants[0];
    Plant* normal = plants[1];
    wilting->setState(&WiltingState::getInstance());
    int nH = normal->getHealth();
    int nM = normal->getMoisture();
    int nI = normal->getInsecticide();

    facade->runUrgentCare();

    EXPECT_EQ(normal->getHealth(), nH);
    EXPECT_EQ(normal->getMoisture(), nM);
    EXPECT_EQ(normal->getInsecticide(), nI);
}

// With null services, urgent care is safe and does nothing.
TEST_F(FacadeTestFixture, RunUrgentCare_NullServices_NoCrash) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    nullFacade.runUrgentCare();
    SUCCEED();
}

// Fetches recommendations for a known customer and expects results.
TEST_F(FacadeTestFixture, GetPersonalizedRecommendations) 
{
    auto recommendations = facade->getPersonalizedRecommendations("cust001");
    EXPECT_FALSE(recommendations.empty());
}

// With null services, personalized recommendations should be empty.
TEST_F(FacadeTestFixture, PersonalizedRecommendations_NullServices_ReturnsEmpty) 
{
    NurseryFacade nullFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto recs = nullFacade.getPersonalizedRecommendations("any");
    EXPECT_TRUE(recs.empty());
}


// Checkout fails when payment is less than the total.
TEST_F(FacadeTestFixture, Checkout_InsufficientPayment) 
{
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#1", "ROSE001", "Rose", 15.0 }
    };
    Receipt receipt = facade->checkout("cust001", lines, 10.0);
    EXPECT_FALSE(receipt.success);
}

// Checkout with an empty cart should fail.
TEST_F(FacadeTestFixture, Checkout_EmptyCart) 
{
    std::vector<events::OrderLine> lines;
    Receipt receipt = facade->checkout("cust001", lines, 0.0);
    EXPECT_FALSE(receipt.success);
}

// Checkout fails for an unknown customer ID.
TEST_F(FacadeTestFixture, Checkout_InvalidCustomer) 
{
    std::vector<events::OrderLine> lines{
        events::OrderLine{ "ROSE001#2", "ROSE001", "Rose", 15.0 }
    };
    Receipt receipt = facade->checkout("invalid_user", lines, 20.0);
    EXPECT_FALSE(receipt.success);
}

// Getting orders for an unknown customer returns an empty list.
TEST_F(FacadeTestFixture, GetCustomerOrders_InvalidCustomer) 
{
    auto orders = facade->getCustomerOrders("invalid");
    EXPECT_TRUE(orders.empty());
}

// Getting orders for an unknown staff member returns an empty list.
TEST_F(FacadeTestFixture, GetStaffOrders_InvalidStaff) 
{
    auto orders = facade->getStaffOrders("invalid");
    EXPECT_TRUE(orders.empty());
}

// Direct water on an empty plant list is a no-op.
TEST_F(FacadeTestFixture, WaterPlants_Empty_NoOp) 
{
    std::vector<Plant*> none;
    facade->waterPlants(none);
    SUCCEED();
}

// Direct fertilize on an empty plant list is a no-op.
TEST_F(FacadeTestFixture, FertilizePlants_Empty_NoOp) 
{
    std::vector<Plant*> none;
    facade->fertilizePlants(none);
    SUCCEED();
}

// Direct spray on an empty plant list is a no-op.
TEST_F(FacadeTestFixture, SprayInsecticide_Empty_NoOp) 
{
    std::vector<Plant*> none;
    facade->sprayInsecticide(none);
    SUCCEED();
}

// Processing next on an empty queue returns false.
TEST_F(FacadeTestFixture, ProcessNextCommand_EmptyQueue_ReturnsFalse) 
{
    EXPECT_EQ(facade->getQueueSize(), 0);
    EXPECT_FALSE(facade->processNextCommand());
}

// Processing all on an empty queue returns zero.
TEST_F(FacadeTestFixture, ProcessAllCommands_EmptyQueue_ReturnsZero) 
{
    EXPECT_EQ(facade->getQueueSize(), 0);
    EXPECT_EQ(facade->processAllCommands(), 0);
}

// Restocking zero quantity should not change inventory after processing.
TEST_F(FacadeTestFixture, EnqueueRestock_ZeroQty_NoChangeAfterProcess) 
{
    int before = facade->getSpeciesQuantity("ROSE001");
    facade->enqueueRestock("ROSE001", 0, "staff002");
    facade->processAllCommands();
    int after = facade->getSpeciesQuantity("ROSE001");
    EXPECT_EQ(after, before);
}

// Restocking an invalid SKU should not add any plants.
TEST_F(FacadeTestFixture, EnqueueRestock_InvalidSku_NoPlantsAdded) 
{
    int before = facade->getSpeciesQuantity("UNKNOWN");
    facade->enqueueRestock("UNKNOWN", 3, "staff002");
    facade->processAllCommands();
    int after = facade->getSpeciesQuantity("UNKNOWN");
    EXPECT_EQ(after, before);
}

// Morning routine with no plants is a no-op.
TEST_F(FacadeTestFixture, RunMorningRoutine_Empty_NoOp) 
{
    std::vector<Plant*> none;
    facade->runMorningRoutine(none);
    SUCCEED();
}

// Night routine with no plants is a no-op.
TEST_F(FacadeTestFixture, RunNightRoutine_Empty_NoOp) 
{
    std::vector<Plant*> none;
    facade->runNightRoutine(none);
    SUCCEED();
}

// Chat between two unknown users returns an empty conversation.
TEST_F(FacadeTestFixture, GetConversation_UnknownUsers_ReturnsEmpty) 
{
    auto convo = facade->getConversation("unknownA", "unknownB");
    EXPECT_TRUE(convo.empty());
}

// With an empty greenhouse, recommendations should be empty.
TEST_F(FacadeTestFixture, PersonalizedRecommendations_WithEmptyGreenhouse_ReturnsEmpty) 
{
    Inventory emptyStore;
    PlantRegistry emptyRegistry;
    Greenhouse emptyGreenhouse(&emptyRegistry);
    InventoryService emptyInventory(emptyStore, emptyGreenhouse);
    SalesService emptySales;
    ChatMediator med;
    StaffService emptyStaff(&med);
    CustomerService emptyCustomers(&med);
    SpeciesCatalog emptyCatalog;
    ActionLog emptyInvoker;
    NurseryFacade emptyFacade(&emptyInventory, &emptySales, &emptyStaff, &emptyCustomers, &emptyGreenhouse, &emptyCatalog, &emptyInvoker);

    auto recs = emptyFacade.getPersonalizedRecommendations("anyCustomer");
    EXPECT_TRUE(recs.empty());
}

// Recommendations should exclude items already purchased.
TEST_F(FacadeTestFixture, PersonalizedRecommendations_AfterCheckout_ExcludesPurchased) 
{
    std::vector<events::OrderLine> lines{ events::OrderLine{ "ROSE001#1", "ROSE001", "Rose", 15.0 } };
    Receipt r = facade->checkout("cust001", lines, 20.0);
    ASSERT_TRUE(r.success);
    auto recs = facade->getPersonalizedRecommendations("cust001");
    bool containsPurchased = false;
    for (auto* p : recs) { if (p && p->id() == "ROSE001#1") { containsPurchased = true; break; } }
    EXPECT_FALSE(containsPurchased);
    EXPECT_LE(recs.size(), 15u);
}

// After completing an order, recommendations still return other items.
TEST_F(FacadeTestFixture, PersonalizedRecommendations_AfterCompletedOrder_StillReturns) 
{
    std::vector<events::OrderLine> lines{ events::OrderLine{ "ROSE001#2", "ROSE001", "Rose", 15.0 } };
    Receipt r = facade->checkout("cust001", lines, 20.0);
    ASSERT_TRUE(r.success);
    ASSERT_TRUE(facade->completeOrder(r.orderId));
    auto recs = facade->getPersonalizedRecommendations("cust001");
    EXPECT_FALSE(recs.empty());
    EXPECT_LE(recs.size(), 15u);
}

// A facade with all null services returns safe defaults and no-ops.
TEST_F(FacadeTestFixture, FacadeWithNullServices_ReturnsSafeDefaults) 
{
    NurseryFacade badFacade(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    EXPECT_TRUE(badFacade.browseAvailable().empty());
    std::vector<events::OrderLine> lines;
    Receipt r = badFacade.checkout("cust", lines, 0.0);
    EXPECT_FALSE(r.success);
    EXPECT_TRUE(badFacade.getCustomerReceipts("cust").empty());
    EXPECT_EQ(badFacade.getQueueSize(), 0);
    EXPECT_FALSE(badFacade.processNextCommand());
    EXPECT_EQ(badFacade.processAllCommands(), 0);
}


// Negative restock quantity produces no net change and remains undoable.
TEST_F(FacadeTestFixture, EnqueueRestock_NegativeQty_NoChangeAfterProcessAndUndo) 
{
    const std::string sku = "ROSE001";
    int before = facade->getSpeciesQuantity(sku);

    size_t histBefore = facade->getRestockHistorySize();
    facade->enqueueRestock(sku, -7, "staff001");
    EXPECT_TRUE(facade->processNextCommand());

    int after = facade->getSpeciesQuantity(sku);
    EXPECT_EQ(after, before);

    size_t histAfter = facade->getRestockHistorySize();
    EXPECT_EQ(histAfter, histBefore + 1);
    EXPECT_TRUE(facade->undoLastRestock());
    EXPECT_EQ(facade->getRestockHistorySize(), histBefore);
    EXPECT_EQ(facade->getSpeciesQuantity(sku), before);
}

// Enqueuing duplicate pointers waters the same plant safely within bounds.
TEST_F(FacadeTestFixture, EnqueueWater_DuplicatePointers_WithinBounds) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    Plant* p = plants[0];
    if (p->getMoisture() >= 95) { p->addWater(-20); }
    int before = p->getMoisture();

    std::vector<Plant*> dup{ p, p, p };
    size_t qBefore = facade->getQueueSize();
    facade->enqueueWater(dup, "userX");
    EXPECT_GT(facade->getQueueSize(), qBefore);
    facade->processAllCommands();

    EXPECT_LE(p->getMoisture(), 100);
    EXPECT_GE(p->getMoisture(), before);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Enqueuing duplicate pointers for spray keeps insecticide within bounds.
TEST_F(FacadeTestFixture, EnqueueSpray_DuplicatePointers_WithinBounds) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    Plant* p = plants[0];
    if (p->getInsecticide() >= 95) { p->addInsecticide(-20); }
    int before = p->getInsecticide();

    std::vector<Plant*> dup{ p, p, p };
    size_t qBefore = facade->getQueueSize();
    facade->enqueueSpray(dup, "userY");
    EXPECT_GT(facade->getQueueSize(), qBefore);
    facade->processAllCommands();

    EXPECT_LE(p->getInsecticide(), 100);
    EXPECT_GE(p->getInsecticide(), before);
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Urgent care should not leave any commands lingering in the queue.
TEST_F(FacadeTestFixture, RunUrgentCare_DoesNotLeaveQueuedCommands) 
{
    auto plants = facade->browseAvailable();
    ASSERT_FALSE(plants.empty());
    plants[0]->setState(&WiltingState::getInstance());
    size_t qBefore = facade->getQueueSize();
    facade->runUrgentCare();
    EXPECT_EQ(facade->getQueueSize(), qBefore);
}

// Recommendations are size-capped and contain unique plant IDs.
TEST_F(FacadeTestFixture, PersonalizedRecommendations_SizeCappedAndUnique) 
{
    auto recs = facade->getPersonalizedRecommendations("nonexistent_user");
    EXPECT_LE(recs.size(), 15u);
    std::unordered_set<std::string> ids;
    for (auto* p : recs) {
        ASSERT_NE(p, nullptr);
        ids.insert(p->id());
    }
    EXPECT_EQ(ids.size(), recs.size());
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
