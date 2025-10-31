/**
 * @file PlantKitFactory.h
 * @brief Declares the abstract PlantKitFactory class for creating plant kits.
 * 
 * Defines the interface for creating Plant objects with environment-specific pots, soil,
 * and care strategies. Supports the Factory Method pattern.
 * 
 * @date 2025-10-31
 */

#ifndef PLANTKITFACTORY_H
#define PLANTKITFACTORY_H

#include <string>
#include "Pot.h"
#include "SoilMix.h"
#include "Plant.h"
#include "PlantState.h"
#include "SeedlingState.h"
#include "PlantFlyweight.h"
#include "CareStrategy.h"

/**
 * @class PlantKitFactory
 * @brief Abstract factory for creating plants and their associated components.
 * 
 * Provides the interface for creating Plant objects along with environment-specific
 * Pot, SoilMix, and CareStrategy. Uses the Factory Method pattern.
 */
class PlantKitFactory 
{
public:

    /**
     * @brief Creates a Plant object with the specified ID, color, and species flyweight.
     * @param id Unique plant identifier.
     * @param colour Color of the plant.
     * @param sf Pointer to the PlantFlyweight species data.
     * @return Pointer to the newly created Plant object.
     */
    Plant* createPlant(std::string id, std::string colour, PlantFlyweight* sf);
	
    /**
     * @brief Returns the environment-specific care strategy.
     * @return Pointer to a CareStrategy instance.
     */
    virtual CareStrategy* careStrategy() = 0;

protected:

    /**
     * @brief Creates a pot suitable for this plant type.
     * @return Pointer to a Pot object.
     */
    virtual Pot* createPot() = 0;

    /**
     * @brief Creates a soil mix suitable for this plant type.
     * @return Pointer to a SoilMix object.
     */
    virtual SoilMix* createSoilMix() = 0;
};

#endif
