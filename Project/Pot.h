/**
 * @file Pot.h
 * @brief Declares the abstract Pot class representing a plant pot.
 * 
 * Pot defines a base interface for pot types, including cost management and cloning.
 * Derived classes must implement the name and clone methods.
 * 
 * @date 2025-10-31
 */

#ifndef POT_H
#define POT_H

#include <iostream>
#include <string>

/**
 * @class Pot
 * @brief Abstract base class for plant pots.
 * 
 * Stores the cost of the pot and defines pure virtual functions for retrieving the pot name
 * and cloning the object (Prototype pattern support).
 */
class Pot 
{
private:
    /// Cost of the pot.
    int cost;

public:

    /**
     * @brief Constructs a Pot with a specified cost.
     * @param c Cost of the pot.
     */
    Pot(int c);

    /// Virtual destructor.
    virtual ~Pot() = default;

    /**
     * @brief Returns the name of the pot type.
     * @return Pot type name as a string.
     */
    virtual std::string name() = 0;

    /**
     * @brief Returns the cost of this pot.
     * @return Cost as an integer.
     */
    int getCost();

    /**
     * @brief Creates a cloned copy of this pot.
     * @return Pointer to the cloned Pot.
     */
    virtual Pot* clone() const = 0;
};

#endif
