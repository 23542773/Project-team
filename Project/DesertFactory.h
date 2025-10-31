/**
 * @file DesertFactory.h
 * @brief Declares the DesertFactory class, a concrete PlantKitFactory for desert plants.
 * 
 * DesertFactory creates plant kits suited for desert environments, including sandy soil,
 * terracotta pots, and a desert-specific care strategy.
 * 
 * @date 2025-10-31
 */

#ifndef DESERTFACTORY_H
#define DESERTFACTORY_H

#include "PlantKitFactory.h"
#include "TerracottaPot.h"
#include "SandySoilMix.h"
#include "CareStrategy.h"
#include "DesertStrategy.h"

/**
 * @class DesertFactory
 * @brief Concrete factory for desert plant kits.
 * 
 * Implements the PlantKitFactory interface to create desert-specific pots and soil mixes,
 * and provides a desert-adapted CareStrategy.
 */
class DesertFactory : public PlantKitFactory
{
    /// Static instance of the DesertStrategy (can be used as singleton).
    static DesertStrategy s;

public:

    /**
     * @brief Returns the desert-specific care strategy.
     * @return Pointer to a CareStrategy instance.
     */
    CareStrategy* careStrategy() override;

protected:

    /**
     * @brief Creates a desert-appropriate pot.
     * @return Pointer to a Pot instance (TerracottaPot).
     */
    Pot* createPot() override;

    /**
     * @brief Creates a desert-appropriate soil mix.
     * @return Pointer to a SoilMix instance (SandySoilMix).
     */
    SoilMix* createSoilMix() override;
};

#endif
