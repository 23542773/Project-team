/**
 * @file test_state.cpp
 * @brief Comprehensive unit tests for State Pattern implementation
 * @date 2025-10-30
 *
 * Tests all state methods, transitions, and boundary conditions
 */

// Compatibility fix for older MinGW
#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
#define gmtime_s(a, b) (*a = *gmtime(b), 0)
#endif

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_COLORS_NONE
#include "doctest.h"
#include "../State (with Singleton)/Plant.h"
#include "../State (with Singleton)/PlantState.h"
#include "../State (with Singleton)/SeedlingState.h"
#include "../State (with Singleton)/GrowingState.h"
#include "../State (with Singleton)/MatureState.h"
#include "../State (with Singleton)/WiltingState.h"
#include "../State (with Singleton)/DeadState.h"

// ============================================================================
// 1. SINGLETON PATTERN VERIFICATION
// ============================================================================

TEST_CASE("State Pattern - Singleton Instances") {

    SUBCASE("All states return same instance") {
        CHECK(&SeedlingState::getInstance() == &SeedlingState::getInstance());
        CHECK(&GrowingState::getInstance() == &GrowingState::getInstance());
        CHECK(&MatureState::getInstance() == &MatureState::getInstance());
        CHECK(&WiltingState::getInstance() == &WiltingState::getInstance());
        CHECK(&DeadState::getInstance() == &DeadState::getInstance());
    }
}

// ============================================================================
// 2. STATE NAME VERIFICATION
// ============================================================================

TEST_CASE("State Pattern - State Names") {

    SUBCASE("All states return correct names") {
        CHECK(SeedlingState::getInstance().name() == "Seedling");
        CHECK(GrowingState::getInstance().name() == "Growing");
        CHECK(MatureState::getInstance().name() == "Matured");
        CHECK(WiltingState::getInstance().name() == "Wilting");
        CHECK(DeadState::getInstance().name() == "Dead");
    }
}

// ============================================================================
// 3. isMature() METHOD VERIFICATION
// ============================================================================

TEST_CASE("State Pattern - isMature Method") {

    SUBCASE("All states return false for isMature") {
        CHECK(SeedlingState::getInstance().isMature() == false);
        CHECK(GrowingState::getInstance().isMature() == false);
        CHECK(MatureState::getInstance().isMature() == false);
        CHECK(WiltingState::getInstance().isMature() == false);
        CHECK(DeadState::getInstance().isMature() == false);
    }
}

// ============================================================================
// 4. SEEDLING STATE - onTick() and checkChange()
// ============================================================================

TEST_CASE("SeedlingState - onTick Behavior") {

    SUBCASE("onTick adds +2 health") {
        Plant plant("test1", "green", nullptr, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);
        plant.addHealth(-20); // Start at 80 health

        int initialHealth = plant.getHealth();
        plant.tickDay();

        CHECK(plant.getHealth() == initialHealth + 2);
    }
}

TEST_CASE("SeedlingState - checkChange Transitions") {

    SUBCASE("Transitions to Growing after 5 days") {
        Plant plant("test2", "green", nullptr, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Seedling");

        for (int i = 0; i < 6; i++) {
            plant.tickDay();
        }

        CHECK(plant.getAgeDays() == 6);
        CHECK(plant.getPlantState()->name() == "Growing");
    }

    SUBCASE("Boundary: Does NOT transition at exactly 5 days") {
        Plant plant("test3", "green", nullptr, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);

        for (int i = 0; i < 5; i++) {
            plant.tickDay();
        }

        CHECK(plant.getAgeDays() == 5);
        CHECK(plant.getPlantState()->name() == "Seedling");
    }

    SUBCASE("Boundary: Transitions at 6 days (age > 5)") {
        Plant plant("test4", "green", nullptr, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);

        for (int i = 0; i < 6; i++) {
            plant.tickDay();
        }

        CHECK(plant.getAgeDays() == 6);
        CHECK(plant.getPlantState()->name() == "Growing");
    }
}

// ============================================================================
// 5. GROWING STATE - onTick() and checkChange()
// ============================================================================

TEST_CASE("GrowingState - onTick Behavior") {

    SUBCASE("onTick adds +1 health and -10 moisture") {
        Plant plant("test5", "green", nullptr, nullptr, &GrowingState::getInstance(), nullptr, nullptr);
        plant.addHealth(-20); // Set health to 80 to see the increase
        plant.addWater(50); // Start with moisture

        int initialHealth = plant.getHealth();
        int initialMoisture = plant.getMoisture();

        plant.tickDay();

        CHECK(plant.getHealth() == initialHealth + 1);
        CHECK(plant.getMoisture() == initialMoisture - 10);
    }
}

TEST_CASE("GrowingState - checkChange Transitions") {

    SUBCASE("Transitions to Mature when age > 12 AND health > 70") {
        Plant plant("test6", "green", nullptr, nullptr, &GrowingState::getInstance(), nullptr, nullptr);

        // Keep watered during growth to prevent wilting
        for (int i = 0; i < 13; i++) {
            plant.addWater(20); // Keep moisture up
            plant.tickDay();
        }

        // Ensure health > 70 (it should be since Growing adds health)
        if (plant.getHealth() <= 70) {
            plant.addHealth(80 - plant.getHealth());
        }

        plant.addWater(50); // Ensure moisture is good
        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Matured");
    }

    SUBCASE("Boundary: Does NOT transition at exactly age 12") {
        Plant plant("test7", "green", nullptr, nullptr, &GrowingState::getInstance(), nullptr, nullptr);

        for (int i = 0; i < 12; i++) {
            plant.tickDay();
        }

        CHECK(plant.getAgeDays() == 12);
        CHECK(plant.getPlantState()->name() == "Growing");
    }

    SUBCASE("Boundary: Does NOT transition if health <= 70 even with age > 12") {
        Plant plant("test8", "green", nullptr, nullptr, &GrowingState::getInstance(), nullptr, nullptr);

        // Start with low health to prevent transition during the loop
        plant.addHealth(50 - plant.getHealth()); // Start at 50

        // Age the plant to > 12 days while keeping health <= 70
        for (int i = 0; i < 13; i++) {
            plant.addWater(50); // Keep well watered
            // Keep health low during loop to prevent premature transition
            if (plant.getHealth() > 65) {
                plant.addHealth(60 - plant.getHealth());
            }
            plant.tickDay();
        }

        // After 13 ticks, age = 13 (> 12), health should be around 60-65
        // Verify state is still Growing (health was kept <= 70)
        CHECK(plant.getPlantState()->name() == "Growing");
    }
}

// ============================================================================
// 6. MATURE STATE - onTick() and checkChange()
// ============================================================================

TEST_CASE("MatureState - onTick Behavior") {

    SUBCASE("onTick removes -15 moisture") {
        Plant plant("test9", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addWater(50);

        int initialMoisture = plant.getMoisture();
        plant.tickDay();

        CHECK(plant.getMoisture() == initialMoisture - 15);
    }

    SUBCASE("onTick removes -3 health if moisture < 30") {
        Plant plant("test10", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addWater(20); // moisture < 30

        int initialHealth = plant.getHealth();
        plant.tickDay();

        CHECK(plant.getHealth() == initialHealth - 3);
    }

    SUBCASE("onTick does NOT remove health if moisture >= 30") {
        Plant plant("test11", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addWater(50); // moisture >= 30

        int initialHealth = plant.getHealth();
        plant.tickDay();

        CHECK(plant.getHealth() == initialHealth);
    }
}

TEST_CASE("MatureState - checkChange Transitions") {

    SUBCASE("Transitions to Wilting when health < 40") {
        Plant plant("test12", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addHealth(-65); // health = 35 (< 40)
        plant.addWater(50);   // moisture ok

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Transitions to Wilting when moisture < 20") {
        Plant plant("test13", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addWater(15); // moisture = 15 (< 20)

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Boundary: Does NOT transition at exactly health = 40") {
        Plant plant("test14", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addHealth(40 - plant.getHealth()); // health = 40
        plant.addWater(50);

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Matured");
    }

    SUBCASE("Boundary: Does NOT transition at exactly moisture = 20") {
        Plant plant("test15", "green", nullptr, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        plant.addWater(35); // Start with 35, after tick: 35 - 15 = 20

        plant.tickDay();

        // After tick, moisture should be 20 (not < 20), so should stay Mature
        CHECK(plant.getMoisture() == 20);
        CHECK(plant.getPlantState()->name() == "Matured");
    }
}

// ============================================================================
// 7. WILTING STATE - onTick() and checkChange()
// ============================================================================

TEST_CASE("WiltingState - onTick Behavior") {

    SUBCASE("onTick removes -5 moisture and -4 health") {
        Plant plant("test16", "green", nullptr, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        plant.addWater(50);
        plant.addHealth(-20); // health = 80

        int initialMoisture = plant.getMoisture();
        int initialHealth = plant.getHealth();

        plant.tickDay();

        CHECK(plant.getMoisture() == initialMoisture - 5);
        CHECK(plant.getHealth() == initialHealth - 4);
    }
}

TEST_CASE("WiltingState - checkChange Transitions") {

    SUBCASE("Transitions to Dead when health <= 0") {
        Plant plant("test17", "green", nullptr, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        plant.addHealth(-100); // health = 0

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Dead");
    }

    SUBCASE("Boundary: Transitions to Dead at exactly health = 0") {
        Plant plant("test18", "green", nullptr, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        plant.addHealth(-100); // health = 0

        plant.tickDay();

        CHECK(plant.getHealth() <= 0);
        CHECK(plant.getPlantState()->name() == "Dead");
    }

    SUBCASE("Recovers to Mature when health > 60 AND moisture > 40") {
        Plant plant("test19", "green", nullptr, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        plant.addHealth(-30); // health = 70 (> 60)
        plant.addWater(50);   // moisture = 50 (> 40)

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Matured");
    }

    SUBCASE("Boundary: Does NOT recover at exactly health = 60") {
        Plant plant("test20", "green", nullptr, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        plant.addHealth(60 - plant.getHealth()); // health = 60
        plant.addWater(50);

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Boundary: Does NOT recover at exactly moisture = 40") {
        Plant plant("test21", "green", nullptr, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        plant.addHealth(-30); // health = 70
        plant.addWater(40);   // moisture = 40

        plant.tickDay();

        CHECK(plant.getPlantState()->name() == "Wilting");
    }
}

// ============================================================================
// 8. DEAD STATE - onTick() and checkChange()
// ============================================================================

TEST_CASE("DeadState - Terminal State Behavior") {

    SUBCASE("onTick does nothing (no-op)") {
        Plant plant("test22", "green", nullptr, nullptr, &DeadState::getInstance(), nullptr, nullptr);
        plant.addHealth(-100);
        plant.addWater(0);

        int initialHealth = plant.getHealth();
        int initialMoisture = plant.getMoisture();

        plant.tickDay();

        // Values should not change (death is permanent)
        CHECK(plant.getHealth() == initialHealth);
        CHECK(plant.getMoisture() == initialMoisture);
    }

    SUBCASE("checkChange never transitions (death is permanent)") {
        Plant plant("test23", "green", nullptr, nullptr, &DeadState::getInstance(), nullptr, nullptr);

        // Try to "revive" by adding health and water
        plant.addHealth(100);
        plant.addWater(100);

        plant.tickDay();

        // Should still be dead
        CHECK(plant.getPlantState()->name() == "Dead");
    }
}

// ============================================================================
// 9. COMPLETE LIFECYCLE TEST
// ============================================================================

TEST_CASE("State Pattern - Complete Lifecycle") {

    SUBCASE("Full lifecycle: Seedling → Growing → Mature → Wilting → Dead") {
        Plant plant("lifecycle", "green", nullptr, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);

        // Phase 1: Seedling (0-5 days)
        CHECK(plant.getPlantState()->name() == "Seedling");

        // Phase 2: Transition to Growing (day 6)
        for (int i = 0; i < 6; i++) {
            plant.tickDay();
        }
        CHECK(plant.getPlantState()->name() == "Growing");

        // Phase 3: Transition to Mature (day 13+, health > 70)
        plant.addWater(100); // Keep watered
        for (int i = 0; i < 8; i++) {
            plant.addWater(20); // Prevent moisture depletion
            plant.tickDay();
        }
        CHECK(plant.getPlantState()->name() == "Matured");

        // Phase 4: Transition to Wilting (by letting health drop)
        plant.addHealth(-70); // health = 30 (< 40)
        plant.tickDay();
        CHECK(plant.getPlantState()->name() == "Wilting");

        // Phase 5: Transition to Dead (by letting health reach 0)
        plant.addHealth(-100);
        plant.tickDay();
        CHECK(plant.getPlantState()->name() == "Dead");
    }
}

// ============================================================================
// 10. EDGE CASES AND NULL HANDLING
// ============================================================================

TEST_CASE("State Pattern - Edge Cases") {

    SUBCASE("Plant with null state doesn't crash") {
        Plant plant("test24", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        CHECK(plant.getPlantState() == nullptr);

        plant.tickDay(); // Should not crash
        CHECK(plant.getAgeDays() == 1); // Age still increments
    }

    SUBCASE("Manual state changes work correctly") {
        Plant plant("test25", "green", nullptr, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Seedling");

        plant.setState(&MatureState::getInstance());
        CHECK(plant.getPlantState()->name() == "Matured");

        plant.setState(&DeadState::getInstance());
        CHECK(plant.getPlantState()->name() == "Dead");
    }
}

// ============================================================================
// 11. BOUNDARY VALUE TESTS
// ============================================================================

TEST_CASE("State Pattern - Boundary Values") {

    SUBCASE("Health boundaries (0 and 100)") {
        Plant plant("test26", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        // Test health = 100 (start)
        CHECK(plant.getHealth() == 100);

        // Test health = 0
        plant.addHealth(-100);
        CHECK(plant.getHealth() >= 0);

        // Test clamping beyond bounds
        plant.addHealth(200);
        CHECK(plant.getHealth() <= 100);
    }

    SUBCASE("Moisture boundaries (0 and 100)") {
        Plant plant("test27", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        // Test moisture = 0 (start)
        CHECK(plant.getMoisture() == 0);

        // Test moisture = 100
        plant.addWater(100);
        CHECK(plant.getMoisture() <= 100);

        // Test negative
        plant.addWater(-200);
        CHECK(plant.getMoisture() >= 0);
    }
}
