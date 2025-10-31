/**
 * @file GlazedCeramicPot.h
 * @brief Declares the GlazedCeramicPot class, a concrete implementation of Pot.
 * 
 * Represents a glazed ceramic pot with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef GLAZEDCERAMICPOT_H
#define GLAZEDCERAMICPOT_H

#include "Pot.h"

/**
 * @class GlazedCeramicPot
 * @brief Concrete Pot representing a glazed ceramic pot.
 */
class GlazedCeramicPot : public Pot
{
public:

    /**
     * @brief Constructs a GlazedCeramicPot with a predefined cost.
     */
    GlazedCeramicPot();

    /**
     * @brief Returns the name of this pot type.
     * @return "GlazedCeramicPot" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this pot.
     * @return Pointer to the cloned GlazedCeramicPot.
     */
    Pot* clone() const override;
};

#endif
