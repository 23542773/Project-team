/**
 * @file TropicalFactory.h
 * @brief Declares the TropicalFactory class, a concrete PlantKitFactory for tropical plants.
 * 
 * TropicalFactory creates plant kits suited for tropical environments, including peat soil,
 * glazed ceramic pots, and a tropical-specific care strategy.
 * 
 * @date 2025-10-31
 */

#ifndef TROPICALFACTORY_H
#define TROPICALFACTORY_H

#include "PlantKitFactory.h"
#include "GlazedCeramicPot.h"
#include "PeatSoilMix.h"
#include "CareStrategy.h"
#include "TropicalStrategy.h"

/**
 * @class TropicalFactory
 * @brief Concrete factory for tropical plant kits.
 * 
 * Implements the PlantKitFactory interface to create tropical-specific pots and soil mixes,
 * and provides a tropical-adapted CareStrategy.
 */
class TropicalFactory : public PlantKitFactory
{
    /// Static instance of the TropicalStrategy (can be used as singleton).
    static TropicalStrategy s;

public:

    /**
     * @brief Returns the tropical-specific care strategy.
     * @return Pointer to a CareStrategy instance.
     */
    CareStrategy* careStrategy() override;

protected:

    /**
     * @brief Creates a tropical-appropriate pot.
     * @return Pointer to a Pot instance (GlazedCeramicPot).
     */
    Pot* createPot() override;

    /**
     * @brief Creates a tropical-appropriate soil mix.
     * @return Pointer to a SoilMix instance (PeatSoilMix).
     */
    SoilMix* createSoilMix() override;
};

#endif
