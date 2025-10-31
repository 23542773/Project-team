/**
 * @file AquaticSoilMix.h
 * @brief Declares the AquaticSoilMix class, a concrete implementation of SoilMix.
 * 
 * Represents an aquatic soil mix with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef AQUATICSOILMIX_H
#define AQUATICSOILMIX_H

#include "SoilMix.h"

/**
 * @class AquaticSoilMix
 * @brief Concrete SoilMix representing an aquatic soil mix.
 */
class AquaticSoilMix : public SoilMix
{
public:

    /**
     * @brief Constructs an AquaticSoilMix with a predefined cost.
     */
    AquaticSoilMix();

    /**
     * @brief Returns the name of this soil type.
     * @return "AquaticSoilMix" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this soil mix.
     * @return Pointer to the cloned AquaticSoilMix.
     */
    SoilMix* clone() const override;
};

#endif
