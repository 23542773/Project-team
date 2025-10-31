/**
 * @file TerracottaPot.h
 * @brief Declares the TerracottaPot class, a concrete implementation of Pot.
 * 
 * Represents a terracotta plant pot with a fixed cost.
 * Supports cloning via the Prototype pattern.
 * 
 * @date 2025-10-31
 */

#ifndef TERRACOTTAPOT_H
#define TERRACOTTAPOT_H

#include "Pot.h"

/**
 * @class TerracottaPot
 * @brief Concrete Pot representing a terracotta pot.
 */
class TerracottaPot : public Pot
{
public:

    /**
     * @brief Constructs a TerracottaPot with a predefined cost.
     */
    TerracottaPot();

    /**
     * @brief Returns the name of this pot type.
     * @return "TerracottaPot" as a string.
     */
    std::string name() override;

    /**
     * @brief Creates a cloned copy of this pot.
     * @return Pointer to the cloned TerracottaPot.
     */
    Pot* clone() const override;
};

#endif
