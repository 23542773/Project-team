/**
 * @file ReinforcedPot.h
 * @brief Declares the ReinforcedPot decorator class for SaleItem objects.
 * 
 * ReinforcedPot is a concrete decorator that adds reinforcement features to a Pot,
 * modifying its cost and description dynamically.
 * 
 * @date 2025-10-31
 */

#ifndef REINFORCEDPOT_H
#define REINFORCEDPOT_H

#include "SaleDecorator.h"
#include <string>

/**
 * @class ReinforcedPot
 * @brief Decorator that adds reinforcement to a Pot.
 * 
 * Inherits from SaleDecorator and wraps a SaleItem, updating cost and description.
 */
class ReinforcedPot : public SaleDecorator 
{
public:

    /**
     * @brief Constructs a ReinforcedPot decorator around an existing SaleItem.
     * @param inner Unique pointer to the SaleItem to decorate.
     */
    explicit ReinforcedPot(std::unique_ptr<SaleItem> inner);

    /**
     * @brief Returns the modified cost of the reinforced pot.
     * @return Cost as a double.
     */
    double cost() override;

    /**
     * @brief Returns the modified description including reinforcement details.
     * @return Description as a string.
     */
    std::string description() override;
};

#endif
