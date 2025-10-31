/**
 * @file LightAirySoilMix.h
 * @brief Declares the LightAirySoilMix class, a concrete implementation of SoilMix.
 * 
 * Represents a light and airy soil mix suitable for indoor plants.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef LIGHTAIRYSOILMIX_H
#define LIGHTAIRYSOILMIX_H

#include "SoilMix.h"

/**
 * @class LightAirySoilMix
 * @brief Concrete SoilMix representing a light, airy soil mix.
 */
class LightAirySoilMix : public SoilMix
{
public:

    /**
     * @brief Constructs a LightAirySoilMix with a predefined cost.
     */
    LightAirySoilMix();

    /**
     * @brief Returns the name of this soil type.
     * @return "LightAirySoilMix" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this soil mix.
     * @return Pointer to the cloned LightAirySoilMix.
     */
    SoilMix* clone() const override;
};

#endif
