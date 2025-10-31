/**
 * @file CeramicPot.h
 * @brief Declares the CeramicPot class, a concrete implementation of Pot.
 * 
 * Represents a standard ceramic pot with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef CERAMICPOT_H
#define CERAMICPOT_H

#include "Pot.h"

/**
 * @class CeramicPot
 * @brief Concrete Pot representing a standard ceramic pot.
 */
class CeramicPot : public Pot
{
public:

    /**
     * @brief Constructs a CeramicPot with a predefined cost.
     */
    CeramicPot();

    /**
     * @brief Returns the name of this pot type.
     * @return "CeramicPot" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this pot.
     * @return Pointer to the cloned CeramicPot.
     */
    Pot* clone() const override;
};

#endif
