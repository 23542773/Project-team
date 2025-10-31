/**
 * @file MediterraneanFactory.h
 * @brief Declares the MediterraneanFactory class, a concrete PlantKitFactory for Mediterranean plants.
 * 
 * MediterraneanFactory creates plant kits suited for Mediterranean environments, including gritty lime soil,
 * unglazed clay pots, and a Mediterranean-specific care strategy.
 * 
 * @date 2025-10-31
 */

#ifndef MEDITERRANEANFACTORY_H
#define MEDITERRANEANFACTORY_H

#include "PlantKitFactory.h"
#include "UnglazedClayPot.h"
#include "GrittyLimeSoilMix.h"
#include "CareStrategy.h"
#include "MediterraneanStrategy.h"

/**
 * @class MediterraneanFactory
 * @brief Concrete factory for Mediterranean plant kits.
 * 
 * Implements the PlantKitFactory interface to create Mediterranean-specific pots and soil mixes,
 * and provides a Mediterranean-adapted CareStrategy.
 */
class MediterraneanFactory : public PlantKitFactory
{
    /// Static instance of the MediterraneanStrategy (can be used as singleton).
    static MediterraneanStrategy s;

public:

    /**
     * @brief Returns the Mediterranean-specific care strategy.
     * @return Pointer to a CareStrategy instance.
     */
    CareStrategy* careStrategy() override;

protected:

    /**
     * @brief Creates a Mediterranean-appropriate pot.
     * @return Pointer to a Pot instance (UnglazedClayPot).
     */
    Pot* createPot() override;

    /**
     * @brief Creates a Mediterranean-appropriate soil mix.
     * @return Pointer to a SoilMix instance (GrittyLimeSoilMix).
     */
    SoilMix* createSoilMix() override;
};

#endif
