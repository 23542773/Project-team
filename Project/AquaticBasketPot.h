/**
 * @file AquaticBasketPot.h
 * @brief Declares the AquaticBasketPot class, a concrete implementation of Pot.
 * 
 * Represents an aquatic basket pot with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef AQUATICBASKETPOT_H
#define AQUATICBASKETPOT_H

#include "Pot.h"

/**
 * @class AquaticBasketPot
 * @brief Concrete Pot representing an aquatic basket pot.
 */
class AquaticBasketPot : public Pot
{
public:

    /**
     * @brief Constructs an AquaticBasketPot with a predefined cost.
     */
    AquaticBasketPot();

    /**
     * @brief Returns the name of this pot type.
     * @return "AquaticBasketPot" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this pot.
     * @return Pointer to the cloned AquaticBasketPot.
     */
    Pot* clone() const override;
};

#endif
