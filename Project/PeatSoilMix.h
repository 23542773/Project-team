/**
 * @file PeatSoilMix.h
 * @brief Declares the PeatSoilMix class, a concrete implementation of SoilMix.
 * 
 * Represents a peat-based soil mix with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef PEATSOILMIX_H
#define PEATSOILMIX_H

#include "SoilMix.h"

/**
 * @class PeatSoilMix
 * @brief Concrete SoilMix representing peat soil.
 */
class PeatSoilMix : public SoilMix
{
public:

    /**
     * @brief Constructs a PeatSoilMix with a predefined cost.
     */
    PeatSoilMix();

    /**
     * @brief Returns the name of this soil type.
     * @return "PeatSoilMix" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this soil mix.
     * @return Pointer to the cloned PeatSoilMix.
     */
    SoilMix* clone() const override;
};

#endif
