/**
 * @file WetlandFactory.h
 * @brief Declares the WetlandFactory class, a concrete PlantKitFactory for wetland plants.
 * 
 * WetlandFactory creates plant kits suited for wetland environments, including aquatic soil,
 * aquatic basket pots, and a wetland-specific care strategy.
 * 
 * @date 2025-10-31
 */

#ifndef WETLANDFACTORY_H
#define WETLANDFACTORY_H

#include "PlantKitFactory.h"
#include "AquaticBasketPot.h"
#include "AquaticSoilMix.h"
#include "CareStrategy.h"
#include "WetlandStrategy.h"

/**
 * @class WetlandFactory
 * @brief Concrete factory for wetland plant kits.
 * 
 * Implements the PlantKitFactory interface to create wetland-specific pots and soil mixes,
 * and provides a wetland-adapted CareStrategy.
 */
class WetlandFactory : public PlantKitFactory
{
    /// Static instance of the WetlandStrategy (can be used as singleton).
    static WetlandStrategy s;

public:

    /**
     * @brief Returns the wetland-specific care strategy.
     * @return Pointer to a CareStrategy instance.
     */
    CareStrategy* careStrategy() override;

protected:

    /**
     * @brief Creates a wetland-appropriate pot.
     * @return Pointer to a Pot instance (AquaticBasketPot).
     */
    Pot* createPot() override;

    /**
     * @brief Creates a wetland-appropriate soil mix.
     * @return Pointer to a SoilMix instance (AquaticSoilMix).
     */
    SoilMix* createSoilMix() override;
};

#endif
