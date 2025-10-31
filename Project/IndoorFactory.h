/**
 * @file IndoorFactory.h
 * @brief Declares the IndoorFactory class, a concrete PlantKitFactory for indoor plants.
 * 
 * IndoorFactory creates plant kits suited for indoor environments, including light airy soil,
 * ceramic pots, and an indoor-specific care strategy.
 * 
 * @date 2025-10-31
 */

#ifndef INDOORFACTORY_H
#define INDOORFACTORY_H

#include "PlantKitFactory.h"
#include "CeramicPot.h"
#include "LightAirySoilMix.h"
#include "CareStrategy.h"
#include "IndoorStrategy.h"

/**
 * @class IndoorFactory
 * @brief Concrete factory for indoor plant kits.
 * 
 * Implements the PlantKitFactory interface to create indoor-specific pots and soil mixes,
 * and provides an indoor-adapted CareStrategy.
 */
class IndoorFactory : public PlantKitFactory
{
    /// Static instance of the IndoorStrategy (can be used as singleton).
    static IndoorStrategy s;

public:

    /**
     * @brief Returns the indoor-specific care strategy.
     * @return Pointer to a CareStrategy instance.
     */
    CareStrategy* careStrategy() override;

protected:

    /**
     * @brief Creates an indoor-appropriate pot.
     * @return Pointer to a Pot instance (CeramicPot).
     */
    Pot* createPot() override;

    /**
     * @brief Creates an indoor-appropriate soil mix.
     * @return Pointer to a SoilMix instance (LightAirySoilMix).
     */
    SoilMix* createSoilMix() override;
};

#endif
