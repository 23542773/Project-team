/**
 * @file SandySoilMix.h
 * @brief Declares the SandySoilMix class, a concrete implementation of SoilMix.
 * 
 * Represents a sandy soil type with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef SANDYSOILMIX_H
#define SANDYSOILMIX_H

#include "SoilMix.h"

/**
 * @class SandySoilMix
 * @brief Concrete SoilMix representing sandy soil.
 */
class SandySoilMix : public SoilMix
{
public:

    /**
     * @brief Constructs a SandySoilMix with a predefined cost.
     */
    SandySoilMix();

    /**
     * @brief Returns the name of this soil type.
     * @return "SandySoilMix" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this soil mix.
     * @return Pointer to the cloned SandySoilMix.
     */
    SoilMix* clone() const override;
};

#endif
