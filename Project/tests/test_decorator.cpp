/**
 * @file test_decorator.cpp
 * @brief Comprehensive unit tests for Decorator Pattern implementation
 * @date 2025-11-01
 *
 * Tests the Decorator pattern including SaleItem (component), PlantItem (concrete component),
 * SaleDecorator (base decorator), and concrete decorators (ReinforcedPot, GiftWrap, MessageCard).
 * Validates cost calculations, description formatting, decorator stacking, and polymorphic behavior.
 */

// Compatibility fix for older MinGW
#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
#define gmtime_s(a, b) (*a = *gmtime(b), 0)
#endif

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_COLORS_NONE
#include "doctest.h"

#include "../SaleItem.h"
#include "../PlantItem.h"
#include "../SaleDecorator.h"
#include "../ReinforcedPot.h"
#include "../GiftWrap.h"
#include "../MessageCard.h"
#include "../Plant.h"
#include "../SpeciesFlyweight.h"
#include "../SeedlingState.h"
#include "../SandySoilMix.h"
#include "../CeramicPot.h"
#include <memory>

// ============================================================================
// TEST 1: BASE COMPONENT - PlantItem without decorators
// ============================================================================

TEST_CASE("PlantItem base component") {
    SpeciesFlyweight species("TEST_ROSE", "Rose", "Garden", 35, 0.5, 0.5, 1.0, Season::Spring);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P001", "Red", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    PlantItem item(&plant);
    CHECK(item.cost() > 0);
    CHECK(item.description().find("Rose") != std::string::npos);
    
}

// ============================================================================
// TEST 2: REINFORCED POT DECORATOR - Adds +80 to cost
// ============================================================================

TEST_CASE("ReinforcedPot decorator") {
    SpeciesFlyweight species("TEST_LILY", "Lily", "Wetland", 40, 0.7, 0.5, 1.0, Season::Summer);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P002", "White", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> decorated(new ReinforcedPot(std::move(item)));
    
    CHECK(decorated->cost() == baseCost + 80.0);
    CHECK(decorated->description().find("Reinforced Pot") != std::string::npos);
    
}

// ============================================================================
// TEST 3: GIFT WRAP DECORATOR - Adds +25 to cost
// ============================================================================

TEST_CASE("GiftWrap decorator") {
    SpeciesFlyweight species("TEST_TULIP", "Tulip", "Garden", 20, 0.5, 0.5, 1.0, Season::Spring);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P003", "Yellow", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> decorated(new GiftWrap(std::move(item)));
    
    CHECK(decorated->cost() == baseCost + 25.0);
    CHECK(decorated->description().find("Gift Wrap") != std::string::npos);
    
}

// ============================================================================
// TEST 4: MESSAGE CARD DECORATOR - Adds +15 with custom message
// ============================================================================

TEST_CASE("MessageCard decorator") {
    SpeciesFlyweight species("TEST_ORCHID", "Orchid", "Tropical", 50, 0.6, 0.4, 0.8, Season::Summer);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P004", "Pink", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> decorated(new MessageCard(std::move(item), "Happy Birthday!"));
    
    CHECK(decorated->cost() == baseCost + 15.0);
    CHECK(decorated->description().find("Card") != std::string::npos);
    CHECK(decorated->description().find("Happy Birthday!") != std::string::npos);
    
}

// ============================================================================
// TEST 5: MULTIPLE DECORATORS - Stacking two decorators
// ============================================================================

TEST_CASE("Multiple decorators - ReinforcedPot and GiftWrap") {
    SpeciesFlyweight species("TEST_CACTUS", "Cactus", "Desert", 15, 0.2, 0.9, 0.5, Season::Summer);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P005", "Green", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> withPot(new ReinforcedPot(std::move(item)));
    std::unique_ptr<SaleItem> withWrap(new GiftWrap(std::move(withPot)));
    
    CHECK(withWrap->cost() == baseCost + 105.0);
    
}

// ============================================================================
// TEST 6: MULTIPLE DECORATORS - Stacking all three decorators (+120 total)
// ============================================================================

TEST_CASE("Multiple decorators - All three") {
    SpeciesFlyweight species("TEST_SUNFLOWER", "Sunflower", "Garden", 25, 0.5, 0.6, 1.2, Season::Summer);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P006", "Yellow", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> withPot(new ReinforcedPot(std::move(item)));
    std::unique_ptr<SaleItem> withCard(new MessageCard(std::move(withPot), "Get Well"));
    std::unique_ptr<SaleItem> withWrap(new GiftWrap(std::move(withCard)));
    
    CHECK(withWrap->cost() == baseCost + 120.0);
    
}

// ============================================================================
// TEST 7: DECORATOR ORDER INDEPENDENCE - Commutative property verification
// ============================================================================

TEST_CASE("Decorator order independence") {
    SpeciesFlyweight species("TEST_IVY", "Ivy", "Indoor", 30, 0.6, 0.5, 0.9, Season::Spring);
    SandySoilMix* soil1 = new SandySoilMix();
    CeramicPot* pot1 = new CeramicPot();
    SandySoilMix* soil2 = new SandySoilMix();
    CeramicPot* pot2 = new CeramicPot();
    Plant plant1("P007A", "Green", &species, nullptr, &SeedlingState::getInstance(), soil1, pot1);
    Plant plant2("P007B", "Green", &species, nullptr, &SeedlingState::getInstance(), soil2, pot2);
    
    std::unique_ptr<SaleItem> item1(new PlantItem(&plant1));
    double baseCost = item1->cost();
    std::unique_ptr<SaleItem> order1_pot(new ReinforcedPot(std::move(item1)));
    std::unique_ptr<SaleItem> order1_wrap(new GiftWrap(std::move(order1_pot)));
    
    std::unique_ptr<SaleItem> item2(new PlantItem(&plant2));
    std::unique_ptr<SaleItem> order2_wrap(new GiftWrap(std::move(item2)));
    std::unique_ptr<SaleItem> order2_pot(new ReinforcedPot(std::move(order2_wrap)));
    
    CHECK(order1_wrap->cost() == order2_pot->cost());
    CHECK(order1_wrap->cost() == baseCost + 105.0);
    
}

// ============================================================================
// TEST 8: DUPLICATE DECORATORS - Applying same decorator multiple times
// ============================================================================

TEST_CASE("Same decorator applied twice") {
    SpeciesFlyweight species("TEST_FERN", "Fern", "Shade", 10, 0.7, 0.5, 1.0, Season::Autumn);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P008", "Green", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> wrap1(new GiftWrap(std::move(item)));
    std::unique_ptr<SaleItem> wrap2(new GiftWrap(std::move(wrap1)));
    
    CHECK(wrap2->cost() == baseCost + 50.0);
    
}

// ============================================================================
// TEST 9: EDGE CASE - MessageCard with empty message string
// ============================================================================

TEST_CASE("MessageCard with empty message") {
    SpeciesFlyweight species("TEST_DAISY", "Daisy", "Garden", 18, 0.5, 0.5, 1.0, Season::Spring);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P009", "White", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::unique_ptr<SaleItem> decorated(new MessageCard(std::move(item), ""));
    
    CHECK(decorated->cost() == baseCost + 15.0);
    CHECK(decorated->description().find("Card") != std::string::npos);
    
}

// ============================================================================
// TEST 10: EDGE CASE - MessageCard with long message (60+ characters)
// ============================================================================

TEST_CASE("MessageCard with long message") {
    SpeciesFlyweight species("TEST_VIOLET", "Violet", "Garden", 12, 0.6, 0.5, 1.0, Season::Spring);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P010", "Purple", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    double baseCost = item->cost();
    std::string longMsg = "Congratulations on your special day! Wishing you all the best!";
    std::unique_ptr<SaleItem> decorated(new MessageCard(std::move(item), longMsg));
    
    CHECK(decorated->cost() == baseCost + 15.0);
    CHECK(decorated->description().find(longMsg) != std::string::npos);
    
}

// ============================================================================
// TEST 11: POLYMORPHISM - Using base SaleItem* pointers with decorators
// ============================================================================

TEST_CASE("Polymorphic SaleItem pointer") {
    SpeciesFlyweight species("TEST_BAMBOO", "Bamboo", "Tropical", 22, 0.7, 0.6, 1.5, Season::Summer);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P011", "Green", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    // Store as base SaleItem pointer - tests polymorphism
    SaleItem* basePtr = new PlantItem(&plant);
    double baseCost = basePtr->cost();
    
    SaleItem* decoratedPtr = new GiftWrap(std::unique_ptr<SaleItem>(basePtr));
    CHECK(decoratedPtr->cost() == baseCost + 25.0);
    
    delete decoratedPtr;
    
}

// ============================================================================
// TEST 12: DESCRIPTION ORDERING - Verify all decorations appear in sequence
// ============================================================================

TEST_CASE("Description contains all decorator info in order") {
    SpeciesFlyweight species("TEST_MARIGOLD", "Marigold", "Garden", 8, 0.5, 0.6, 1.0, Season::Autumn);
    SandySoilMix* soil = new SandySoilMix();
    CeramicPot* pot = new CeramicPot();
    Plant plant("P012", "Orange", &species, nullptr, &SeedlingState::getInstance(), soil, pot);
    
    std::unique_ptr<SaleItem> item(new PlantItem(&plant));
    std::unique_ptr<SaleItem> withPot(new ReinforcedPot(std::move(item)));
    std::unique_ptr<SaleItem> withCard(new MessageCard(std::move(withPot), "Special"));
    std::unique_ptr<SaleItem> withWrap(new GiftWrap(std::move(withCard)));
    
    std::string desc = withWrap->description();
    
    // All decorations should appear in the description
    CHECK(desc.find("Marigold") != std::string::npos);
    CHECK(desc.find("Reinforced Pot") != std::string::npos);
    CHECK(desc.find("Card") != std::string::npos);
    CHECK(desc.find("Special") != std::string::npos);
    CHECK(desc.find("Gift Wrap") != std::string::npos);
    
    // Check they appear in the right order (inner to outer)
    size_t basePos = desc.find("Marigold");
    size_t potPos = desc.find("Reinforced Pot");
    size_t cardPos = desc.find("Card");
    size_t wrapPos = desc.find("Gift Wrap");
    
    CHECK(basePos < potPos);
    CHECK(potPos < cardPos);
    CHECK(cardPos < wrapPos);
    
}
