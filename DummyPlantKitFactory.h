#ifndef DUMMY_PLANTKITFACTORY_H
#define DUMMY_PLANTKITFACTORY_H

#include <string>
#include "PlantKitFactory.h"

/**
 * @file dummy/DummyPlantKitFactory.h
 * @brief Standalone dummy PlantKitFactory for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real PlantKitFactory implementation
 */

// Forward declarations
class DummyPlant;
class DummyPlantFlyweight;

/**
 * @class DummyPot
 * @brief Simple dummy pot - standalone
 */
class DummyPot {
private:
    std::string potName;
public:
    DummyPot(const std::string& name) : potName(name) {}
    std::string name() const { return potName; }
};

/**
 * @class DummySoilMix
 * @brief Simple dummy soil mix - standalone
 */
class DummySoilMix {
private:
    std::string soilName;
public:
    DummySoilMix(const std::string& name) : soilName(name) {}
    std::string name() const { return soilName; }
};

/**
 * @class DummyPlantKitFactory
 * @brief Standalone dummy factory - NO INHERITANCE
 * 
 * When real PlantKitFactory is ready, change this to inherit from PlantKitFactory.
 */
class DummyPlantKitFactory : public PlantKitFactory {
private:
    std::string envType;

public:
    /**
     * @brief Constructor
     * @param environment Environment type (Indoor, Desert, etc.)
     */
    DummyPlantKitFactory(const std::string& environment);

    /**
     * @brief Create a plant
     * @param id Plant identifier
     * @param species Plant species data
     * @return Created DummyPlant
     */
    DummyPlant* createPlant(const std::string& id, DummyPlantFlyweight* species);

    /**
     * @brief Create a pot suitable for this environment
     * @return Created DummyPot
     */
    DummyPot* createPot();

    /**
     * @brief Create soil mixture suitable for this environment
     * @return Created DummySoilMix
     */
    DummySoilMix* createSoilMix();

    /**
     * @brief Get factory environment type
     * @return Environment name (e.g., "Indoor", "Desert")
     */
    std::string getEnvironmentType() const;
};

#endif // DUMMY_PLANTKITFACTORY_H