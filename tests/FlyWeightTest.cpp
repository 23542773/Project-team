#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/SpeciesCatalog.h"
#include "../include/SpeciesKey.h"
#include "../include/SpeciesFlyweight.h"
#include "../include/UnsharedSpeciesFlyweight.h"
#include "../include/PlantFlyweight.h"
#include "../include/CarePresets.h"
#include <memory>

TEST_CASE("SpeciesFlyweight Tests") {
    SUBCASE("SpeciesFlyweight creation and access") {
        SpeciesFlyweight flyweight("SKU123", "Rose", "Temperate", 25);
        
        CHECK(flyweight.getSku() == "SKU123");
        CHECK(flyweight.getName() == "Rose");
        CHECK(flyweight.getBiome() == "Temperate");
        CHECK(flyweight.getCost() == 25);
    }
    
    SUBCASE("SpeciesFlyweight multiple calls consistency") {
        SpeciesFlyweight flyweight("SKU456", "Cactus", "Desert", 15);
        
        CHECK(flyweight.getSku() == "SKU456");
        CHECK(flyweight.getSku() == "SKU456"); // Consistent
        CHECK(flyweight.getName() == "Cactus");
        CHECK(flyweight.getBiome() == "Desert");
        CHECK(flyweight.getCost() == 15);
    }
}

TEST_CASE("UnsharedSpeciesFlyweight Tests") {
    SUBCASE("UnsharedSpeciesFlyweight creation and access") {
        UnsharedSpeciesFlyweight flyweight("SKU789", "Orchid", "Tropical", 35);
        
        CHECK(flyweight.getSku() == "SKU789");
        CHECK(flyweight.getName() == "Orchid");
        CHECK(flyweight.getBiome() == "Tropical");
        CHECK(flyweight.getCost() == 35);
    }
    
    SUBCASE("UnsharedSpeciesFlyweight independent instances") {
        UnsharedSpeciesFlyweight flyweight1("SKU001", "Fern", "Indoor", 20);
        UnsharedSpeciesFlyweight flyweight2("SKU002", "Fern", "Indoor", 25); // Same name, different price
        
        CHECK(flyweight1.getName() == flyweight2.getName());
        CHECK(flyweight1.getCost() != flyweight2.getCost()); // Different costs
    }
}

TEST_CASE("SpeciesCatalog Tests") {
    SUBCASE("SpeciesCatalog add and get") {
        SpeciesCatalog catalog;
        auto flyweight = std::make_shared<SpeciesFlyweight>("SKU100", "Lavender", "Mediterranean", 18);
        
        catalog.add(flyweight);
        auto retrieved = catalog.get("SKU100");
        
        CHECK(retrieved != nullptr);
        CHECK(retrieved->getSku() == "SKU100");
        CHECK(retrieved->getName() == "Lavender");
        CHECK(retrieved->getCost() == 18);
    }
    
    SUBCASE("SpeciesCatalog get non-existent SKU") {
        SpeciesCatalog catalog;
        auto retrieved = catalog.get("NON_EXISTENT");
        CHECK(retrieved == nullptr);
    }
    
    SUBCASE("SpeciesCatalog has method") {
        SpeciesCatalog catalog;
        auto flyweight = std::make_shared<SpeciesFlyweight>("SKU200", "Tulip", "Temperate", 12);
        
        catalog.add(flyweight);
        CHECK(catalog.has("SKU200") == true);
        CHECK(catalog.has("SKU999") == false);
    }
    
    SUBCASE("SpeciesCatalog remove method") {
        SpeciesCatalog catalog;
        auto flyweight = std::make_shared<SpeciesFlyweight>("SKU300", "Sunflower", "Temperate", 8);
        
        catalog.add(flyweight);
        CHECK(catalog.has("SKU300") == true);
        
        catalog.remove("SKU300");
        CHECK(catalog.has("SKU300") == false);
        CHECK(catalog.get("SKU300") == nullptr);
    }
    
    SUBCASE("SpeciesCatalog multiple species") {
        SpeciesCatalog catalog;
        
        auto rose = std::make_shared<SpeciesFlyweight>("SKU_ROSE", "Rose", "Temperate", 25);
        auto cactus = std::make_shared<SpeciesFlyweight>("SKU_CACTUS", "Cactus", "Desert", 15);
        
        catalog.add(rose);
        catalog.add(cactus);
        
        auto retrievedRose = catalog.get("SKU_ROSE");
        auto retrievedCactus = catalog.get("SKU_CACTUS");
        
        CHECK(retrievedRose->getName() == "Rose");
        CHECK(retrievedCactus->getName() == "Cactus");
        CHECK(retrievedRose->getBiome() == "Temperate");
        CHECK(retrievedCactus->getBiome() == "Desert");
    }
    
    SUBCASE("SpeciesCatalog flyweight sharing") {
        SpeciesCatalog catalog;
        auto flyweight = std::make_shared<SpeciesFlyweight>("SKU400", "Fern", "Indoor", 20);
        
        catalog.add(flyweight);
        auto first = catalog.get("SKU400");
        auto second = catalog.get("SKU400");
        
        // Should be the same shared object
        CHECK(first == second);
        CHECK(first->getSku() == "SKU400");
        CHECK(second->getName() == "Fern");
    }
    
    SUBCASE("SpeciesCatalog overwrite existing SKU") {
        SpeciesCatalog catalog;
        
        auto first = std::make_shared<SpeciesFlyweight>("SKU500", "First", "Biome1", 10);
        auto second = std::make_shared<SpeciesFlyweight>("SKU500", "Second", "Biome2", 20); // Same SKU
        
        catalog.add(first);
        catalog.add(second); // Should overwrite
        
        auto retrieved = catalog.get("SKU500");
        CHECK(retrieved->getName() == "Second"); // Gets the last one added
        CHECK(retrieved->getBiome() == "Biome2");
        CHECK(retrieved->getCost() == 20);
    }
}

TEST_CASE("Flyweight Memory Efficiency") {
    SUBCASE("Multiple retrievals return same instance") {
        SpeciesCatalog catalog;
        auto original = std::make_shared<SpeciesFlyweight>("SKU800", "Lily", "Temperate", 22);
        
        catalog.add(original);
        
        auto first = catalog.get("SKU800");
        auto second = catalog.get("SKU800");
        auto third = catalog.get("SKU800");
        
        // All should be the exact same shared_ptr
        CHECK(first == second);
        CHECK(second == third);
        CHECK(first == third);
        CHECK(first->getSku() == "SKU800");
    }
}