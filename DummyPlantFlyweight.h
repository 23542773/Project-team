#ifndef DUMMY_PLANTFLYWEIGHT_H
#define DUMMY_PLANTFLYWEIGHT_H

#include <string>

/**
 * @file dummy/DummyPlantFlyweight.h
 * @brief Standalone dummy implementation of PlantFlyweight for testing
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real PlantFlyweight implementation
 */

struct DummyCarePresets {
    int baseWaterInMl;
    int idealLightInHours;
    int fertilizeFreqInDays;
};

/**
 * @class DummyPlantFlyweight
 * @brief Standalone dummy species data - NO INHERITANCE
 * 
 * This is a temporary dummy class that mimics PlantFlyweight interface
 * WITHOUT inheriting from it. When real PlantFlyweight is ready,
 * simply change this to inherit from PlantFlyweight instead.
 */
class DummyPlantFlyweight {
private:
    std::string speciesName_;
    std::string environment_;
    DummyCarePresets carePresets_;

public:
    /**
     * @brief Create dummy species with hardcoded data
     * 
     * @param type Type identifier (hardcoded)
     *   - "aloe": Aloe Vera (Indoor succulent)
     *   - "cactus": Desert Rose (Desert plant)
     *   - "orchid": Orchid (Tropical)
     *   - "lavender": Lavender (Mediterranean)
     *   - "fern": Boston Fern (Wetland/Tropical)
     */
    DummyPlantFlyweight(const std::string& type);

    /**
     * @brief Get species common name
     * @return Species name
     */
    std::string speciesName() const;

    /**
     * @brief Get environment type
     * @return Environment (Indoor, Desert, Tropical, etc.)
     */
    std::string envType() const;

    /**
     * @brief Get care requirements
     * @return DummyCarePresets with water, light, fertilizer info
     */
    DummyCarePresets careDefaults() const;

    /**
     * @brief Get all available dummy types
     * @return String listing available types
     */
    static const char* getAvailableTypes() {
        return "aloe, cactus, orchid, lavender, fern";
    }
};

#endif // DUMMY_PLANTFLYWEIGHT_H