/**
 * @file SoilMix.h
 * @brief Declares the abstract SoilMix class representing a type of soil composition.
 * 
 * SoilMix defines a base interface for soil types, including cost management and cloning.
 * Derived classes must implement the name and clone methods.
 * 
 * @date 2025-10-31
 */

#ifndef SOILMIX_H
#define SOILMIX_H

#include <iostream>
#include <string>

/**
 * @class SoilMix
 * @brief Abstract base class for soil types.
 * 
 * Stores the cost of the soil and defines pure virtual functions for retrieving the soil name
 * and cloning the object (Prototype pattern support).
 */
class SoilMix 
{
private:
    /// Cost of the soil mix.
    int cost;

public:

    /**
     * @brief Constructs a SoilMix with a specified cost.
     * @param c Cost of the soil mix.
     */
    SoilMix(int c);

    /// Virtual destructor.
    virtual ~SoilMix() = default;

    /**
     * @brief Returns the name of the soil type.
     * @return Soil type name as a string.
     */
    virtual std::string name() = 0;

    /**
     * @brief Returns the cost of this soil mix.
     * @return Cost as an integer.
     */
    int getCost() const;

    /**
     * @brief Creates a cloned copy of this soil mix.
     * @return Pointer to the cloned SoilMix.
     */
    virtual SoilMix* clone() const = 0;
};

#endif
