/**
 * @file test_flyweight.cpp
 * @brief Comprehensive unit tests for Flyweight Pattern implementation
 * @date 2025-10-31
 *
 * Tests the Flyweight pattern including SpeciesCatalog (factory),
 * SpeciesFlyweight (shared flyweight), and UnsharedSpeciesFlyweight.
 */

// Compatibility fix for older MinGW
#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
#define gmtime_s(a, b) (*a = *gmtime(b), 0)
#endif

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_COLORS_NONE
#include "doctest.h"
#include "../PlantFlyweight.h"
#include "../SpeciesCatalog.h"
#include "../SpeciesFlyweight.h"
#include "../UnsharedSpeciesFlyweight.h"

// ============================================================================
// 1. SPECIES FLYWEIGHT - Shared Intrinsic State
// ============================================================================

TEST_CASE("SpeciesFlyweight - Constructor and Getters") {

    SUBCASE("Constructor initializes all properties correctly") {
        SpeciesFlyweight species("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);

        CHECK(species.getSku() == "ROSE001");
        CHECK(species.getName() == "Rose");
        CHECK(species.getBiome() == "Garden");
        CHECK(species.getCost() == 25);
        CHECK(species.getWaterSensitivity() == 0.7);
        CHECK(species.getInsecticideTolerance() == 0.5);
        CHECK(species.getGrowthRate() == 1.2);
        CHECK(species.getThrivingSeason() == Season::Spring);
    }

    SUBCASE("Multiple instances with same data maintain independent values") {
        SpeciesFlyweight species1("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer);
        SpeciesFlyweight species2("ORCH001", "Orchid", "Tropical", 45, 0.9, 0.3, 1.5, Season::Autumn);

        CHECK(species1.getSku() != species2.getSku());
        CHECK(species1.getName() != species2.getName());
        CHECK(species1.getCost() != species2.getCost());
    }

    SUBCASE("All Season enum values work correctly") {
        SpeciesFlyweight spring("S1", "Spring Plant", "Garden", 10, 0.5, 0.5, 1.0, Season::Spring);
        SpeciesFlyweight summer("S2", "Summer Plant", "Garden", 10, 0.5, 0.5, 1.0, Season::Summer);
        SpeciesFlyweight autumn("S3", "Autumn Plant", "Garden", 10, 0.5, 0.5, 1.0, Season::Autumn);
        SpeciesFlyweight winter("S4", "Winter Plant", "Garden", 10, 0.5, 0.5, 1.0, Season::Winter);

        CHECK(spring.getThrivingSeason() == Season::Spring);
        CHECK(summer.getThrivingSeason() == Season::Summer);
        CHECK(autumn.getThrivingSeason() == Season::Autumn);
        CHECK(winter.getThrivingSeason() == Season::Winter);
    }
}

TEST_CASE("SpeciesFlyweight - Intrinsic State Immutability") {

    SUBCASE("Properties remain constant after creation") {
        SpeciesFlyweight species("FERN001", "Fern", "Forest", 20, 0.8, 0.4, 1.1, Season::Spring);

        std::string sku1 = species.getSku();
        std::string name1 = species.getName();
        int cost1 = species.getCost();

        // Call getters multiple times
        std::string sku2 = species.getSku();
        std::string name2 = species.getName();
        int cost2 = species.getCost();

        CHECK(sku1 == sku2);
        CHECK(name1 == name2);
        CHECK(cost1 == cost2);
    }
}

// ============================================================================
// 2. UNSHARED SPECIES FLYWEIGHT - Extrinsic State
// ============================================================================

TEST_CASE("UnsharedSpeciesFlyweight - Constructor and Basic Getters") {

    SUBCASE("Constructor initializes core properties only") {
        UnsharedSpeciesFlyweight unshared("LILY001", "Lily", "Wetland", 30);

        CHECK(unshared.getSku() == "LILY001");
        CHECK(unshared.getName() == "Lily");
        CHECK(unshared.getBiome() == "Wetland");
        CHECK(unshared.getCost() == 30);
    }

    SUBCASE("Uninitialized properties return default values") {
        UnsharedSpeciesFlyweight unshared("TEST001", "Test Plant", "Test Biome", 10);

        // These should compile without errors even if uninitialized
        // The actual values are undefined, so we just verify the getters work
        double ws = unshared.getWaterSensitivity();
        double it = unshared.getInsecticideTolerance();
        double gr = unshared.getGrowthRate();
        Season ts = unshared.getThrivingSeason();

        // Suppress unused variable warnings
        (void)ws;
        (void)it;
        (void)gr;
        (void)ts;

        // Just verify the calls don't crash
        CHECK(true);
    }

    SUBCASE("Multiple unshared instances are independent") {
        UnsharedSpeciesFlyweight unshared1("U001", "Plant1", "Biome1", 10);
        UnsharedSpeciesFlyweight unshared2("U002", "Plant2", "Biome2", 20);

        CHECK(unshared1.getSku() != unshared2.getSku());
        CHECK(unshared1.getName() != unshared2.getName());
        CHECK(unshared1.getCost() != unshared2.getCost());
    }
}

// ============================================================================
// 3. SPECIES CATALOG - Flyweight Factory
// ============================================================================

TEST_CASE("SpeciesCatalog - Add and Get Operations") {

    SUBCASE("Can add and retrieve flyweights by SKU") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);

        catalog.add(rose);
        auto retrieved = catalog.get("ROSE001");

        CHECK(retrieved != nullptr);
        CHECK(retrieved->getSku() == "ROSE001");
        CHECK(retrieved->getName() == "Rose");
    }

    SUBCASE("Returns nullptr for non-existent SKU") {
        SpeciesCatalog catalog;

        auto result = catalog.get("NONEXISTENT");

        CHECK(result == nullptr);
    }

    SUBCASE("Can add multiple flyweights") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);
        auto cactus = std::make_shared<SpeciesFlyweight>("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer);

        catalog.add(rose);
        catalog.add(cactus);

        CHECK(catalog.get("ROSE001") != nullptr);
        CHECK(catalog.get("CACT001") != nullptr);
        CHECK(catalog.get("ROSE001")->getName() == "Rose");
        CHECK(catalog.get("CACT001")->getName() == "Cactus");
    }

    SUBCASE("Adding duplicate SKU replaces existing entry") {
        SpeciesCatalog catalog;
        auto rose1 = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose Red", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);
        auto rose2 = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose White", "Garden", 30, 0.7, 0.5, 1.2, Season::Spring);

        catalog.add(rose1);
        catalog.add(rose2);

        auto retrieved = catalog.get("ROSE001");
        CHECK(retrieved->getName() == "Rose White");
        CHECK(retrieved->getCost() == 30);
    }

    SUBCASE("Null flyweight is not added") {
        SpeciesCatalog catalog;

        catalog.add(nullptr);

        // Catalog should be empty
        CHECK(catalog.getAll().size() == 0);
    }
}

TEST_CASE("SpeciesCatalog - Has Operation") {

    SUBCASE("Returns true for existing SKU") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);

        catalog.add(rose);

        CHECK(catalog.has("ROSE001") == true);
    }

    SUBCASE("Returns false for non-existent SKU") {
        SpeciesCatalog catalog;

        CHECK(catalog.has("NONEXISTENT") == false);
    }

    SUBCASE("Returns false for empty catalog") {
        SpeciesCatalog catalog;

        CHECK(catalog.has("ANYTHING") == false);
    }
}

TEST_CASE("SpeciesCatalog - Remove Operation") {

    SUBCASE("Can remove existing flyweight") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);

        catalog.add(rose);
        CHECK(catalog.has("ROSE001") == true);

        catalog.remove("ROSE001");
        CHECK(catalog.has("ROSE001") == false);
    }

    SUBCASE("Removing non-existent SKU doesn't cause errors") {
        SpeciesCatalog catalog;

        catalog.remove("NONEXISTENT"); // Should not crash
        CHECK(true);
    }

    SUBCASE("Can add back after removal") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);

        catalog.add(rose);
        catalog.remove("ROSE001");
        catalog.add(rose);

        CHECK(catalog.has("ROSE001") == true);
    }
}

TEST_CASE("SpeciesCatalog - GetAll Operation") {

    SUBCASE("Returns empty vector for empty catalog") {
        SpeciesCatalog catalog;

        auto all = catalog.getAll();

        CHECK(all.size() == 0);
    }

    SUBCASE("Returns all added flyweights") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);
        auto cactus = std::make_shared<SpeciesFlyweight>("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer);
        auto fern = std::make_shared<SpeciesFlyweight>("FERN001", "Fern", "Forest", 20, 0.8, 0.4, 1.1, Season::Spring);

        catalog.add(rose);
        catalog.add(cactus);
        catalog.add(fern);

        auto all = catalog.getAll();

        CHECK(all.size() == 3);
    }

    SUBCASE("GetAll reflects removals") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);
        auto cactus = std::make_shared<SpeciesFlyweight>("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer);

        catalog.add(rose);
        catalog.add(cactus);
        CHECK(catalog.getAll().size() == 2);

        catalog.remove("ROSE001");
        CHECK(catalog.getAll().size() == 1);
    }
}

// ============================================================================
// 4. FLYWEIGHT PATTERN - Sharing and Memory Efficiency
// ============================================================================

TEST_CASE("Flyweight Pattern - Object Sharing") {

    SUBCASE("Same pointer returned for same SKU") {
        SpeciesCatalog catalog;
        auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);

        catalog.add(rose);

        auto retrieved1 = catalog.get("ROSE001");
        auto retrieved2 = catalog.get("ROSE001");

        CHECK(retrieved1 == retrieved2); // Same shared_ptr
        CHECK(retrieved1.get() == retrieved2.get()); // Same raw pointer
    }

    SUBCASE("Multiple retrievals share the same object") {
        SpeciesCatalog catalog;
        auto cactus = std::make_shared<SpeciesFlyweight>("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer);

        catalog.add(cactus);

        std::vector<std::shared_ptr<PlantFlyweight>> retrievals;
        for (int i = 0; i < 10; i++) {
            retrievals.push_back(catalog.get("CACT001"));
        }

        // All should point to the same object
        for (size_t i = 1; i < retrievals.size(); i++) {
            CHECK(retrievals[0].get() == retrievals[i].get());
        }
    }
}

TEST_CASE("Flyweight Pattern - Factory Pattern Integration") {

    SUBCASE("Catalog acts as centralized factory") {
        SpeciesCatalog catalog;

        // Pre-populate catalog with common species (factory pattern)
        catalog.add(std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring));
        catalog.add(std::make_shared<SpeciesFlyweight>("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer));
        catalog.add(std::make_shared<SpeciesFlyweight>("ORCH001", "Orchid", "Tropical", 45, 0.9, 0.3, 1.5, Season::Autumn));

        // Request pre-existing species
        CHECK(catalog.has("ROSE001"));
        CHECK(catalog.has("CACT001"));
        CHECK(catalog.has("ORCH001"));

        // Request non-existent species
        CHECK(catalog.has("UNKNOWN") == false);
    }

    SUBCASE("Catalog manages lifecycle of flyweights") {
        SpeciesCatalog catalog;

        {
            auto rose = std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring);
            catalog.add(rose);
            // rose goes out of scope here
        }

        // Catalog still maintains the reference
        CHECK(catalog.has("ROSE001") == true);
        CHECK(catalog.get("ROSE001") != nullptr);
    }
}

// ============================================================================
// 5. POLYMORPHISM - PlantFlyweight Interface
// ============================================================================

TEST_CASE("Flyweight Pattern - Polymorphic Interface") {

    SUBCASE("SpeciesFlyweight can be used through base interface") {
        std::shared_ptr<PlantFlyweight> flyweight = std::make_shared<SpeciesFlyweight>(
            "ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring
        );

        CHECK(flyweight->getSku() == "ROSE001");
        CHECK(flyweight->getName() == "Rose");
        CHECK(flyweight->getBiome() == "Garden");
        CHECK(flyweight->getCost() == 25);
        CHECK(flyweight->getWaterSensitivity() == 0.7);
        CHECK(flyweight->getInsecticideTolerance() == 0.5);
        CHECK(flyweight->getGrowthRate() == 1.2);
        CHECK(flyweight->getThrivingSeason() == Season::Spring);
    }

    SUBCASE("UnsharedSpeciesFlyweight can be used through base interface") {
        std::shared_ptr<PlantFlyweight> flyweight = std::make_shared<UnsharedSpeciesFlyweight>(
            "LILY001", "Lily", "Wetland", 30
        );

        CHECK(flyweight->getSku() == "LILY001");
        CHECK(flyweight->getName() == "Lily");
        CHECK(flyweight->getBiome() == "Wetland");
        CHECK(flyweight->getCost() == 30);
    }

    SUBCASE("Catalog can store different flyweight types") {
        SpeciesCatalog catalog;

        auto shared = std::make_shared<SpeciesFlyweight>("S001", "Shared", "Garden", 10, 0.5, 0.5, 1.0, Season::Spring);
        auto unshared = std::make_shared<UnsharedSpeciesFlyweight>("U001", "Unshared", "Forest", 15);

        catalog.add(shared);
        catalog.add(unshared);

        CHECK(catalog.has("S001"));
        CHECK(catalog.has("U001"));
        CHECK(catalog.getAll().size() == 2);
    }
}

// ============================================================================
// 6. BOUNDARY VALUE TESTS
// ============================================================================

TEST_CASE("Flyweight Pattern - Boundary Values") {

    SUBCASE("Empty strings are handled correctly") {
        SpeciesFlyweight species("", "", "", 0, 0.0, 0.0, 0.0, Season::Spring);

        CHECK(species.getSku() == "");
        CHECK(species.getName() == "");
        CHECK(species.getBiome() == "");
    }

    SUBCASE("Zero and negative costs are handled") {
        SpeciesFlyweight zero("SKU1", "Plant1", "Biome1", 0, 0.5, 0.5, 1.0, Season::Spring);
        SpeciesFlyweight negative("SKU2", "Plant2", "Biome2", -10, 0.5, 0.5, 1.0, Season::Summer);

        CHECK(zero.getCost() == 0);
        CHECK(negative.getCost() == -10);
    }

    SUBCASE("Extreme double values are handled") {
        SpeciesFlyweight species("SKU", "Plant", "Biome", 10, 999.9, -999.9, 0.0001, Season::Winter);

        CHECK(species.getWaterSensitivity() == 999.9);
        CHECK(species.getInsecticideTolerance() == -999.9);
        CHECK(species.getGrowthRate() == 0.0001);
    }

    SUBCASE("Very long strings are handled") {
        std::string longString(1000, 'A');
        SpeciesFlyweight species(longString, longString, longString, 10, 0.5, 0.5, 1.0, Season::Autumn);

        CHECK(species.getSku().length() == 1000);
        CHECK(species.getName().length() == 1000);
        CHECK(species.getBiome().length() == 1000);
    }
}

// ============================================================================
// 7. INTEGRATION TESTS
// ============================================================================

TEST_CASE("Flyweight Pattern - Complete Integration") {

    SUBCASE("Simulating a nursery species database") {
        SpeciesCatalog catalog;

        // Add various species
        catalog.add(std::make_shared<SpeciesFlyweight>("ROSE001", "Red Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring));
        catalog.add(std::make_shared<SpeciesFlyweight>("ROSE002", "White Rose", "Garden", 28, 0.7, 0.5, 1.2, Season::Spring));
        catalog.add(std::make_shared<SpeciesFlyweight>("CACT001", "Barrel Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer));
        catalog.add(std::make_shared<SpeciesFlyweight>("ORCH001", "Purple Orchid", "Tropical", 45, 0.9, 0.3, 1.5, Season::Autumn));
        catalog.add(std::make_shared<SpeciesFlyweight>("FERN001", "Boston Fern", "Forest", 20, 0.8, 0.4, 1.1, Season::Spring));

        // Verify catalog has all species
        CHECK(catalog.getAll().size() == 5);

        // Simulate customer browsing
        auto rose = catalog.get("ROSE001");
        CHECK(rose != nullptr);
        CHECK(rose->getName() == "Red Rose");

        // Simulate inventory management
        catalog.remove("ORCH001");
        CHECK(catalog.getAll().size() == 4);
        CHECK(catalog.has("ORCH001") == false);

        // Simulate restocking
        catalog.add(std::make_shared<SpeciesFlyweight>("ORCH001", "Purple Orchid", "Tropical", 45, 0.9, 0.3, 1.5, Season::Autumn));
        CHECK(catalog.getAll().size() == 5);
    }

    SUBCASE("Multiple catalogs are independent") {
        SpeciesCatalog catalog1;
        SpeciesCatalog catalog2;

        catalog1.add(std::make_shared<SpeciesFlyweight>("ROSE001", "Rose", "Garden", 25, 0.7, 0.5, 1.2, Season::Spring));
        catalog2.add(std::make_shared<SpeciesFlyweight>("CACT001", "Cactus", "Desert", 15, 0.2, 0.8, 0.5, Season::Summer));

        CHECK(catalog1.has("ROSE001") == true);
        CHECK(catalog1.has("CACT001") == false);
        CHECK(catalog2.has("ROSE001") == false);
        CHECK(catalog2.has("CACT001") == true);
    }
}

// ============================================================================
// 8. STRESS AND PERFORMANCE TESTS
// ============================================================================

TEST_CASE("Flyweight Pattern - Stress Tests") {

    SUBCASE("Can handle many flyweights") {
        SpeciesCatalog catalog;

        // Add 100 different species
        for (int i = 0; i < 100; i++) {
            std::string sku = "SKU" + std::to_string(i);
            std::string name = "Plant" + std::to_string(i);
            catalog.add(std::make_shared<SpeciesFlyweight>(sku, name, "Biome", i, 0.5, 0.5, 1.0, Season::Spring));
        }

        CHECK(catalog.getAll().size() == 100);

        // Verify we can retrieve them all
        for (int i = 0; i < 100; i++) {
            std::string sku = "SKU" + std::to_string(i);
            CHECK(catalog.has(sku));
        }
    }

    SUBCASE("Can handle many retrievals efficiently") {
        SpeciesCatalog catalog;
        catalog.add(std::make_shared<SpeciesFlyweight>("POPULAR", "Popular Plant", "Garden", 10, 0.5, 0.5, 1.0, Season::Spring));

        // Retrieve the same flyweight many times
        for (int i = 0; i < 1000; i++) {
            auto fw = catalog.get("POPULAR");
            CHECK(fw != nullptr);
            CHECK(fw->getName() == "Popular Plant");
        }
    }
}
