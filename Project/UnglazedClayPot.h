/**
 * @file UnglazedClayPot.h
 * @brief Declares the UnglazedClayPot class, a concrete implementation of Pot.
 * 
 * Represents an unglazed clay pot with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef UNGLAZEDCLAYPOT_H
#define UNGLAZEDCLAYPOT_H

#include "Pot.h"

/**
 * @class UnglazedClayPot
 * @brief Concrete Pot representing an unglazed clay pot.
 */
class UnglazedClayPot : public Pot
{
public:

    /**
     * @brief Constructs an UnglazedClayPot with a predefined cost.
     */
    UnglazedClayPot();

    /**
     * @brief Returns the name of this pot type.
     * @return "UnglazedClayPot" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this pot.
     * @return Pointer to the cloned UnglazedClayPot.
     */
    Pot* clone() const override;
};

#endif
