/**
 * @file test_state.cpp
 * @brief Unit tests for State Pattern implementation
 * @date 2025-10-31
 *
 * Tests state transitions (forward and backward) and terminal state behavior
 */

// Compatibility fix for older MinGW
#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
#define gmtime_s(a, b) (*a = *gmtime(b), 0)
#endif

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_COLORS_NONE
#include "doctest.h"
#include "../Plant.h"
#include "../PlantState.h"
#include "../SeedlingState.h"
#include "../GrowingState.h"
#include "../MatureState.h"
#include "../WiltingState.h"
#include "../DeadState.h"
#include "../SpeciesFlyweight.h"

// ============================================================================
// TEST 1: SINGLETON PATTERN VERIFICATION
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
// TEST 2: STATE NAME VERIFICATION
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
// TEST 3: isMature() METHOD VERIFICATION
// ============================================================================

TEST_CASE("State Pattern - isMature Method") {
    SUBCASE("Only MatureState returns true for isMature") {
        CHECK(SeedlingState::getInstance().isMature() == false);
        CHECK(GrowingState::getInstance().isMature() == false);
        CHECK(MatureState::getInstance().isMature() == true);
        CHECK(WiltingState::getInstance().isMature() == false);
        CHECK(DeadState::getInstance().isMature() == false);
    }
}

// ============================================================================
// TEST 4: FORWARD STATE TRANSITIONS (Health-based deterioration)
// ============================================================================

TEST_CASE("State Pattern - Forward State Transitions") {

    SUBCASE("Growing → Dead (complete health depletion)") {
        SpeciesFlyweight species("TEST001", "Test Plant", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("forward1", "green", &species, nullptr, &GrowingState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Growing");

        // Completely deplete health
        plant.addHealth(-100);
        plant.getPlantState()->checkChange(plant);

        // Should transition to Dead when health <= 0
        CHECK(plant.getPlantState()->name() == "Dead");
    }

    SUBCASE("Growing → Wilting (low health)") {
        SpeciesFlyweight species("TEST002", "Test Plant 2", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("forward2", "green", &species, nullptr, &GrowingState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Growing");

        // Reduce health to wilting threshold
        plant.addHealth(-85); // Health = 15
        plant.getPlantState()->checkChange(plant);

        // Should transition to Wilting when health <= 20
        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Mature → Wilting (mature plant declining)") {
        SpeciesFlyweight species("TEST003", "Test Plant 3", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("forward3", "green", &species, nullptr, &MatureState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Matured");

        // Reduce health below threshold for mature plants
        plant.addHealth(-55); // Health = 45
        plant.getPlantState()->checkChange(plant);

        // Should transition to Wilting when health <= 50
        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Mature → Dead (complete health depletion)") {
        SpeciesFlyweight species("TEST004", "Test Plant 4", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("forward4", "green", &species, nullptr, &MatureState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Matured");

        // Completely deplete health
        plant.addHealth(-100);
        plant.getPlantState()->checkChange(plant);

        // Should transition to Dead
        CHECK(plant.getPlantState()->name() == "Dead");
    }
}

// ============================================================================
// TEST 5: BACKWARD STATE TRANSITIONS (RECOVERY)
// ============================================================================

TEST_CASE("State Pattern - Backward State Transitions (Recovery)") {

    SUBCASE("Wilting → Mature (recovery from wilting)") {
        SpeciesFlyweight species("TEST005", "Test Plant 5", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("backward1", "green", &species, nullptr, &WiltingState::getInstance(), nullptr, nullptr);

        // Start in Wilting state
        CHECK(plant.getPlantState()->name() == "Wilting");

        // Provide excellent care to trigger recovery
        // Need health > 60, moisture > 40, insecticide > 40
        plant.addHealth(70 - plant.getHealth()); // Set to 70
        plant.addWater(70);
        plant.addInsecticide(70);

        // Trigger state check
        plant.getPlantState()->checkChange(plant);

        // Should recover to Mature
        CHECK(plant.getPlantState()->name() == "Matured");
    }

    SUBCASE("Wilting stays Wilting with insufficient health") {
        SpeciesFlyweight species("TEST006", "Test Plant 6", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("backward2", "green", &species, nullptr, &WiltingState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Wilting");

        // Provide resources but keep health low enough to prevent recovery
        // checkChange adds +5 health if moisture > 60 and insecticide > 60
        // So we need to ensure health + 5 is still <= 60
        plant.addHealth(55 - plant.getHealth()); // Set to 55
        plant.addWater(70);
        plant.addInsecticide(70);

        plant.getPlantState()->checkChange(plant);

        // After checkChange: health becomes 55 + 5 = 60 (not > 60)
        // Should remain Wilting because health is not > 60
        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Wilting stays Wilting with insufficient moisture") {
        SpeciesFlyweight species("TEST007", "Test Plant 7", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("backward3", "green", &species, nullptr, &WiltingState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Wilting");

        // Good health but insufficient moisture
        plant.addHealth(70 - plant.getHealth()); // Set to 70
        plant.addWater(40); // Exactly 40, need > 40
        plant.addInsecticide(70);

        plant.getPlantState()->checkChange(plant);

        // Should remain Wilting
        CHECK(plant.getPlantState()->name() == "Wilting");
    }

    SUBCASE("Complete cycle: Mature → Wilting → Mature (forward then backward)") {
        SpeciesFlyweight species("TEST008", "Test Plant 8", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("cycle", "green", &species, nullptr, &MatureState::getInstance(), nullptr, nullptr);

        // Start Mature
        CHECK(plant.getPlantState()->name() == "Matured");

        // FORWARD: Decline to Wilting
        plant.addHealth(40 - plant.getHealth()); // Health = 40
        plant.addWater(10);
        plant.getPlantState()->checkChange(plant);
        CHECK(plant.getPlantState()->name() == "Wilting");

        // BACKWARD: Recover back to Mature
        plant.addHealth(70 - plant.getHealth()); // Health = 70
        plant.addWater(70);
        plant.addInsecticide(70);
        plant.getPlantState()->checkChange(plant);
        CHECK(plant.getPlantState()->name() == "Matured");
    }
}

// ============================================================================
// TEST 6: FINAL/TERMINAL STATE - DeadState has no outgoing transitions
// ============================================================================

TEST_CASE("State Pattern - DeadState is Final/Terminal") {

    SUBCASE("Dead state never transitions - no outgoing states") {
        SpeciesFlyweight species("TEST009", "Dead Plant Test", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("dead1", "brown", &species, nullptr, &DeadState::getInstance(), nullptr, nullptr);

        // Confirm starts as Dead
        CHECK(plant.getPlantState()->name() == "Dead");

        // Try to "revive" with maximum care
        plant.addHealth(100);
        plant.addWater(100);
        plant.addInsecticide(100);

        // Try triggering state changes multiple times
        for (int i = 0; i < 20; i++) {
            plant.getPlantState()->checkChange(plant);
            plant.addHealth(100);
            plant.addWater(100);
            plant.addInsecticide(100);
        }

        // Should STILL be Dead - no transitions from Dead state
        CHECK(plant.getPlantState()->name() == "Dead");
    }

    SUBCASE("Dead state checkChange() does nothing") {
        SpeciesFlyweight species("TEST010", "Dead Plant Test 2", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("dead2", "brown", &species, nullptr, &DeadState::getInstance(), nullptr, nullptr);

        CHECK(plant.getPlantState()->name() == "Dead");

        // Call checkChange directly
        DeadState::getInstance().checkChange(plant);

        // Should still be Dead
        CHECK(plant.getPlantState()->name() == "Dead");
    }

    SUBCASE("Transition to Dead is permanent from any state") {
        SpeciesFlyweight species("TEST011", "Dying Plant", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);

        // Test from Seedling
        Plant p1("dying1", "green", &species, nullptr, &SeedlingState::getInstance(), nullptr, nullptr);
        p1.setState(&DeadState::getInstance());
        p1.addHealth(100);
        p1.getPlantState()->checkChange(p1);
        CHECK(p1.getPlantState()->name() == "Dead");

        // Test from Growing
        Plant p2("dying2", "green", &species, nullptr, &GrowingState::getInstance(), nullptr, nullptr);
        p2.setState(&DeadState::getInstance());
        p2.addHealth(100);
        p2.getPlantState()->checkChange(p2);
        CHECK(p2.getPlantState()->name() == "Dead");

        // Test from Mature
        Plant p3("dying3", "green", &species, nullptr, &MatureState::getInstance(), nullptr, nullptr);
        p3.setState(&DeadState::getInstance());
        p3.addHealth(100);
        p3.getPlantState()->checkChange(p3);
        CHECK(p3.getPlantState()->name() == "Dead");

        // Test from Wilting
        Plant p4("dying4", "green", &species, nullptr, &WiltingState::getInstance(), nullptr, nullptr);
        p4.setState(&DeadState::getInstance());
        p4.addHealth(100);
        p4.getPlantState()->checkChange(p4);
        CHECK(p4.getPlantState()->name() == "Dead");

        // All should remain Dead - terminal state
        CHECK(p1.getPlantState()->name() == "Dead");
        CHECK(p2.getPlantState()->name() == "Dead");
        CHECK(p3.getPlantState()->name() == "Dead");
        CHECK(p4.getPlantState()->name() == "Dead");
    }

    SUBCASE("Dead state reached through natural health depletion from Wilting") {
        SpeciesFlyweight species("TEST012", "Neglected Plant", "Indoor", 100,
                                 0.5, 0.5, 1.0, Season::Spring);
        Plant plant("natural_death", "green", &species, nullptr, &WiltingState::getInstance(), nullptr, nullptr);

        // Start wilting
        CHECK(plant.getPlantState()->name() == "Wilting");

        // Deplete health completely
        plant.addHealth(-200);
        plant.getPlantState()->checkChange(plant);

        // Should be Dead
        CHECK(plant.getPlantState()->name() == "Dead");
        CHECK(plant.getHealth() <= 0);

        // Cannot recover
        plant.addHealth(100);
        plant.getPlantState()->checkChange(plant);
        CHECK(plant.getPlantState()->name() == "Dead");
    }
}
