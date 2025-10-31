/**
 * @file test_strategy.cpp
 * @brief Comprehensive unit tests for Strategy Pattern implementation
 * @date 2025-10-30
 *
 * Tests all strategy methods, behaviors, and boundary conditions
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
#include "../CareStrategy.h"
#include "../DesertStrategy.h"
#include "../TropicalStrategy.h"
#include "../IndoorStrategy.h"
#include "../MediterraneanStrategy.h"
#include "../WetlandStrategy.h"

// ============================================================================
// 1. DESERT STRATEGY - water() and fertilize()
// ============================================================================

TEST_CASE("DesertStrategy - water Method") {

    DesertStrategy desert;

    SUBCASE("Waters when moisture < 30 (adds +15)") {
        Plant plant("cactus1", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addWater(20); // moisture = 20 (< 30)

        desert.water(plant);

        CHECK(plant.getMoisture() == 35); // 20 + 15
    }

    SUBCASE("Does NOT water when moisture >= 30") {
        Plant plant("cactus2", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addWater(50); // moisture = 50 (>= 30)

        desert.water(plant);

        CHECK(plant.getMoisture() == 50); // No change
    }

    SUBCASE("Boundary: Waters at exactly moisture = 29") {
        Plant plant("cactus3", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addWater(29);

        desert.water(plant);

        CHECK(plant.getMoisture() == 44); // 29 + 15
    }

    SUBCASE("Boundary: Does NOT water at exactly moisture = 30") {
        Plant plant("cactus4", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addWater(30);

        desert.water(plant);

        CHECK(plant.getMoisture() == 30); // No change
    }
}

TEST_CASE("DesertStrategy - fertilize Method") {

    DesertStrategy desert;

    SUBCASE("Fertilizes when health < 80 (adds +5)") {
        Plant plant("cactus5", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addHealth(-30); // health = 70 (< 80)

        desert.fertilize(plant);

        CHECK(plant.getHealth() == 75); // 70 + 5
    }

    SUBCASE("Does NOT fertilize when health >= 80") {
        Plant plant("cactus6", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        // health = 100 (>= 80)

        desert.fertilize(plant);

        CHECK(plant.getHealth() == 100); // No change
    }

    SUBCASE("Boundary: Fertilizes at exactly health = 79") {
        Plant plant("cactus7", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addHealth(79 - plant.getHealth());

        desert.fertilize(plant);

        CHECK(plant.getHealth() == 84); // 79 + 5
    }

    SUBCASE("Boundary: Does NOT fertilize at exactly health = 80") {
        Plant plant("cactus8", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addHealth(80 - plant.getHealth());

        desert.fertilize(plant);

        CHECK(plant.getHealth() == 80); // No change
    }
}

// ============================================================================
// 2. TROPICAL STRATEGY - water() and fertilize()
// ============================================================================

TEST_CASE("TropicalStrategy - water Method") {

    TropicalStrategy tropical;

    SUBCASE("Waters when moisture < 70 (adds +25)") {
        Plant plant("orchid1", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addWater(50); // moisture = 50 (< 70)

        tropical.water(plant);

        CHECK(plant.getMoisture() == 75); // 50 + 25
    }

    SUBCASE("Does NOT water when moisture >= 70") {
        Plant plant("orchid2", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addWater(80); // moisture = 80 (>= 70)

        tropical.water(plant);

        CHECK(plant.getMoisture() == 80); // No change
    }

    SUBCASE("Boundary: Waters at exactly moisture = 69") {
        Plant plant("orchid3", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addWater(69);

        tropical.water(plant);

        CHECK(plant.getMoisture() == 94); // 69 + 25
    }

    SUBCASE("Boundary: Does NOT water at exactly moisture = 70") {
        Plant plant("orchid4", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addWater(70);

        tropical.water(plant);

        CHECK(plant.getMoisture() == 70); // No change
    }
}

TEST_CASE("TropicalStrategy - fertilize Method") {

    TropicalStrategy tropical;

    SUBCASE("Fertilizes when health < 90 (adds +10)") {
        Plant plant("orchid5", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addHealth(-20); // health = 80 (< 90)

        tropical.fertilize(plant);

        CHECK(plant.getHealth() == 90); // 80 + 10
    }

    SUBCASE("Does NOT fertilize when health >= 90") {
        Plant plant("orchid6", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        // health = 100 (>= 90)

        tropical.fertilize(plant);

        CHECK(plant.getHealth() == 100); // No change
    }

    SUBCASE("Boundary: Fertilizes at exactly health = 89") {
        Plant plant("orchid7", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addHealth(89 - plant.getHealth());

        tropical.fertilize(plant);

        CHECK(plant.getHealth() == 99); // 89 + 10
    }

    SUBCASE("Boundary: Does NOT fertilize at exactly health = 90") {
        Plant plant("orchid8", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);
        plant.addHealth(90 - plant.getHealth());

        tropical.fertilize(plant);

        CHECK(plant.getHealth() == 90); // No change
    }
}

// ============================================================================
// 3. INDOOR STRATEGY - water() and fertilize()
// ============================================================================

TEST_CASE("IndoorStrategy - water Method") {

    IndoorStrategy indoor;

    SUBCASE("Waters when moisture < 60 (adds +20)") {
        Plant plant("pothos1", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addWater(40); // moisture = 40 (< 60)

        indoor.water(plant);

        CHECK(plant.getMoisture() == 60); // 40 + 20
    }

    SUBCASE("Does NOT water when moisture >= 60") {
        Plant plant("pothos2", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addWater(70); // moisture = 70 (>= 60)

        indoor.water(plant);

        CHECK(plant.getMoisture() == 70); // No change
    }

    SUBCASE("Boundary: Waters at exactly moisture = 59") {
        Plant plant("pothos3", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addWater(59);

        indoor.water(plant);

        CHECK(plant.getMoisture() == 79); // 59 + 20
    }

    SUBCASE("Boundary: Does NOT water at exactly moisture = 60") {
        Plant plant("pothos4", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addWater(60);

        indoor.water(plant);

        CHECK(plant.getMoisture() == 60); // No change
    }
}

TEST_CASE("IndoorStrategy - fertilize Method") {

    IndoorStrategy indoor;

    SUBCASE("Fertilizes when health < 85 (adds +7)") {
        Plant plant("pothos5", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addHealth(-20); // health = 80 (< 85)

        indoor.fertilize(plant);

        CHECK(plant.getHealth() == 87); // 80 + 7
    }

    SUBCASE("Does NOT fertilize when health >= 85") {
        Plant plant("pothos6", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        // health = 100 (>= 85)

        indoor.fertilize(plant);

        CHECK(plant.getHealth() == 100); // No change
    }

    SUBCASE("Boundary: Fertilizes at exactly health = 84") {
        Plant plant("pothos7", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addHealth(84 - plant.getHealth());

        indoor.fertilize(plant);

        CHECK(plant.getHealth() == 91); // 84 + 7
    }

    SUBCASE("Boundary: Does NOT fertilize at exactly health = 85") {
        Plant plant("pothos8", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        plant.addHealth(85 - plant.getHealth());

        indoor.fertilize(plant);

        CHECK(plant.getHealth() == 85); // No change
    }
}

// ============================================================================
// 4. MEDITERRANEAN STRATEGY - water() and fertilize()
// ============================================================================

TEST_CASE("MediterraneanStrategy - water Method") {

    MediterraneanStrategy med;

    SUBCASE("Waters when moisture < 50 (adds +20)") {
        Plant plant("lavender1", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addWater(30); // moisture = 30 (< 50)

        med.water(plant);

        CHECK(plant.getMoisture() == 50); // 30 + 20
    }

    SUBCASE("Does NOT water when moisture >= 50") {
        Plant plant("lavender2", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addWater(60); // moisture = 60 (>= 50)

        med.water(plant);

        CHECK(plant.getMoisture() == 60); // No change
    }

    SUBCASE("Boundary: Waters at exactly moisture = 49") {
        Plant plant("lavender3", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addWater(49);

        med.water(plant);

        CHECK(plant.getMoisture() == 69); // 49 + 20
    }

    SUBCASE("Boundary: Does NOT water at exactly moisture = 50") {
        Plant plant("lavender4", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addWater(50);

        med.water(plant);

        CHECK(plant.getMoisture() == 50); // No change
    }
}

TEST_CASE("MediterraneanStrategy - fertilize Method") {

    MediterraneanStrategy med;

    SUBCASE("Fertilizes when health < 85 (adds +8)") {
        Plant plant("lavender5", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addHealth(-30); // health = 70 (< 85)

        med.fertilize(plant);

        CHECK(plant.getHealth() == 78); // 70 + 8
    }

    SUBCASE("Does NOT fertilize when health >= 85") {
        Plant plant("lavender6", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        // health = 100 (>= 85)

        med.fertilize(plant);

        CHECK(plant.getHealth() == 100); // No change
    }

    SUBCASE("Boundary: Fertilizes at exactly health = 84") {
        Plant plant("lavender7", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addHealth(84 - plant.getHealth());

        med.fertilize(plant);

        CHECK(plant.getHealth() == 92); // 84 + 8
    }

    SUBCASE("Boundary: Does NOT fertilize at exactly health = 85") {
        Plant plant("lavender8", "purple", nullptr, &med, nullptr, nullptr, nullptr);
        plant.addHealth(85 - plant.getHealth());

        med.fertilize(plant);

        CHECK(plant.getHealth() == 85); // No change
    }
}

// ============================================================================
// 5. WETLAND STRATEGY - water() and fertilize()
// ============================================================================

TEST_CASE("WetlandStrategy - water Method") {

    WetlandStrategy wetland;

    SUBCASE("Waters when moisture < 80 (adds +30)") {
        Plant plant("lily1", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addWater(60); // moisture = 60 (< 80)

        wetland.water(plant);

        CHECK(plant.getMoisture() == 90); // 60 + 30
    }

    SUBCASE("Does NOT water when moisture >= 80") {
        Plant plant("lily2", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addWater(90); // moisture = 90 (>= 80)

        wetland.water(plant);

        CHECK(plant.getMoisture() == 90); // No change
    }

    SUBCASE("Boundary: Waters at exactly moisture = 79") {
        Plant plant("lily3", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addWater(79);

        wetland.water(plant);

        // 79 + 30 = 109, but should be clamped to 100
        CHECK(plant.getMoisture() <= 100);
        CHECK(plant.getMoisture() >= 100); // Should be exactly 100 if clamped
    }

    SUBCASE("Boundary: Does NOT water at exactly moisture = 80") {
        Plant plant("lily4", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addWater(80);

        wetland.water(plant);

        CHECK(plant.getMoisture() == 80); // No change
    }
}

TEST_CASE("WetlandStrategy - fertilize Method") {

    WetlandStrategy wetland;

    SUBCASE("Fertilizes when health < 90 (adds +12)") {
        Plant plant("lily5", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addHealth(-30); // health = 70 (< 90)

        wetland.fertilize(plant);

        CHECK(plant.getHealth() == 82); // 70 + 12
    }

    SUBCASE("Does NOT fertilize when health >= 90") {
        Plant plant("lily6", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        // health = 100 (>= 90)

        wetland.fertilize(plant);

        CHECK(plant.getHealth() == 100); // No change
    }

    SUBCASE("Boundary: Fertilizes at exactly health = 89") {
        Plant plant("lily7", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addHealth(89 - plant.getHealth());

        wetland.fertilize(plant);

        // 89 + 12 = 101, but should be clamped to 100
        CHECK(plant.getHealth() <= 100);
        CHECK(plant.getHealth() >= 100); // Should be exactly 100 if clamped
    }

    SUBCASE("Boundary: Does NOT fertilize at exactly health = 90") {
        Plant plant("lily8", "white", nullptr, &wetland, nullptr, nullptr, nullptr);
        plant.addHealth(90 - plant.getHealth());

        wetland.fertilize(plant);

        CHECK(plant.getHealth() == 90); // No change
    }
}

// ============================================================================
// 6. STRATEGY PATTERN INTEGRATION - Plant delegates to strategy
// ============================================================================

TEST_CASE("Strategy Pattern - Plant Delegation") {

    SUBCASE("Plant can be created with a strategy") {
        DesertStrategy desert;
        Plant plant("test1", "red", nullptr, &desert, nullptr, nullptr, nullptr);

        CHECK(plant.getCareStrategy() == &desert);
    }

    SUBCASE("Plant delegates water() to strategy") {
        DesertStrategy desert;
        Plant plant("cactus", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addWater(20); // Below desert threshold

        int before = plant.getMoisture();
        plant.water(); // Should delegate to DesertStrategy

        CHECK(plant.getMoisture() == before + 15);
    }

    SUBCASE("Plant delegates fertilize() to strategy") {
        DesertStrategy desert;
        Plant plant("cactus", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        plant.addHealth(-30); // Below desert threshold

        int before = plant.getHealth();
        plant.fertilize(); // Should delegate to DesertStrategy

        CHECK(plant.getHealth() == before + 5);
    }

    SUBCASE("Different plants use different strategies") {
        DesertStrategy desert;
        TropicalStrategy tropical;

        Plant cactus("cactus", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        Plant orchid("orchid", "purple", nullptr, &tropical, nullptr, nullptr, nullptr);

        CHECK(cactus.getCareStrategy() == &desert);
        CHECK(orchid.getCareStrategy() == &tropical);
        CHECK(cactus.getCareStrategy() != orchid.getCareStrategy());
    }
}

// ============================================================================
// 7. NULL STRATEGY HANDLING
// ============================================================================

TEST_CASE("Strategy Pattern - Null Strategy") {

    SUBCASE("Plant can be created without strategy") {
        Plant plant("test", "blue", nullptr, nullptr, nullptr, nullptr, nullptr);

        CHECK(plant.getCareStrategy() == nullptr);
    }

    SUBCASE("Plant with null strategy doesn't crash on water()") {
        Plant plant("test", "blue", nullptr, nullptr, nullptr, nullptr, nullptr);

        plant.water(); // Should not crash
        // No assertion needed - just verify no crash
    }

    SUBCASE("Plant with null strategy doesn't crash on fertilize()") {
        Plant plant("test", "blue", nullptr, nullptr, nullptr, nullptr, nullptr);

        plant.fertilize(); // Should not crash
        // No assertion needed - just verify no crash
    }
}

// ============================================================================
// 8. PLANT HELPER METHODS - addWater() and addHealth()
// ============================================================================

TEST_CASE("Plant Helper Methods") {

    SUBCASE("addWater increases moisture") {
        Plant plant("test", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        CHECK(plant.getMoisture() == 0);

        plant.addWater(30);
        CHECK(plant.getMoisture() == 30);

        plant.addWater(20);
        CHECK(plant.getMoisture() == 50);
    }

    SUBCASE("addHealth modifies health") {
        Plant plant("test", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        CHECK(plant.getHealth() == 100);

        plant.addHealth(-20);
        CHECK(plant.getHealth() == 80);

        plant.addHealth(10);
        CHECK(plant.getHealth() == 90);
    }

    SUBCASE("Moisture is clamped to 0-100 range") {
        Plant plant("test", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        // Test upper bound
        plant.addWater(150);
        CHECK(plant.getMoisture() <= 100);

        // Test lower bound
        plant.addWater(-200);
        CHECK(plant.getMoisture() >= 0);
    }

    SUBCASE("Health is clamped to 0-100 range") {
        Plant plant("test", "green", nullptr, nullptr, nullptr, nullptr, nullptr);

        // Test upper bound
        plant.addHealth(50); // 100 + 50 = 150, should clamp to 100
        CHECK(plant.getHealth() <= 100);

        // Test lower bound
        plant.addHealth(-200);
        CHECK(plant.getHealth() >= 0);
    }
}

// ============================================================================
// 9. STRATEGY COMPARISON - Different strategies behave differently
// ============================================================================

TEST_CASE("Strategy Pattern - Strategy Comparison") {

    SUBCASE("All strategies have different water thresholds and amounts") {
        DesertStrategy desert;
        TropicalStrategy tropical;
        IndoorStrategy indoor;
        MediterraneanStrategy med;
        WetlandStrategy wetland;

        Plant d("d", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        Plant t("t", "green", nullptr, &tropical, nullptr, nullptr, nullptr);
        Plant i("i", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        Plant m("m", "green", nullptr, &med, nullptr, nullptr, nullptr);
        Plant w("w", "green", nullptr, &wetland, nullptr, nullptr, nullptr);

        // Set all to moisture = 40
        d.addWater(40);
        t.addWater(40);
        i.addWater(40);
        m.addWater(40);
        w.addWater(40);

        // Apply strategies
        desert.water(d);      // Desert: 40 >= 30, no water added
        tropical.water(t);    // Tropical: 40 < 70, adds +25 = 65
        indoor.water(i);      // Indoor: 40 < 60, adds +20 = 60
        med.water(m);         // Med: 40 < 50, adds +20 = 60
        wetland.water(w);     // Wetland: 40 < 80, adds +30 = 70

        CHECK(d.getMoisture() == 40);  // No change
        CHECK(t.getMoisture() == 65);  // 40 + 25
        CHECK(i.getMoisture() == 60);  // 40 + 20
        CHECK(m.getMoisture() == 60);  // 40 + 20
        CHECK(w.getMoisture() == 70);  // 40 + 30
    }

    SUBCASE("All strategies have different fertilize thresholds and amounts") {
        DesertStrategy desert;
        TropicalStrategy tropical;
        IndoorStrategy indoor;
        MediterraneanStrategy med;
        WetlandStrategy wetland;

        Plant d("d", "green", nullptr, &desert, nullptr, nullptr, nullptr);
        Plant t("t", "green", nullptr, &tropical, nullptr, nullptr, nullptr);
        Plant i("i", "green", nullptr, &indoor, nullptr, nullptr, nullptr);
        Plant m("m", "green", nullptr, &med, nullptr, nullptr, nullptr);
        Plant w("w", "green", nullptr, &wetland, nullptr, nullptr, nullptr);

        // Set all to health = 70
        d.addHealth(70 - d.getHealth());
        t.addHealth(70 - t.getHealth());
        i.addHealth(70 - i.getHealth());
        m.addHealth(70 - m.getHealth());
        w.addHealth(70 - w.getHealth());

        // Apply strategies
        desert.fertilize(d);      // Desert: 70 < 80, adds +5 = 75
        tropical.fertilize(t);    // Tropical: 70 < 90, adds +10 = 80
        indoor.fertilize(i);      // Indoor: 70 < 85, adds +7 = 77
        med.fertilize(m);         // Med: 70 < 85, adds +8 = 78
        wetland.fertilize(w);     // Wetland: 70 < 90, adds +12 = 82

        CHECK(d.getHealth() == 75);  // 70 + 5
        CHECK(t.getHealth() == 80);  // 70 + 10
        CHECK(i.getHealth() == 77);  // 70 + 7
        CHECK(m.getHealth() == 78);  // 70 + 8
        CHECK(w.getHealth() == 82);  // 70 + 12
    }
}
