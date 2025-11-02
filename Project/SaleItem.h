/**
 * @file SaleItem.h
 * @brief Defines the abstract base Component interface for the Decorator pattern
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef SALEITEM_H
#define SALEITEM_H
#include <memory>
#include <string>
#include "Plant.h"

/**
 * @class SaleItem
 * @brief Abstract Component class in the Decorator pattern representing items for sale
 *
 * This class defines the interface for all sale items in the nursery system.
 * It serves as the base component that can be decorated with additional features
 * such as reinforced pots, gift wrapping, and message cards.
 *
 * The Decorator pattern allows dynamic addition of responsibilities to sale items
 * without modifying the core SaleItem interface or its concrete implementations.
 */
class SaleItem 
{
public:
/**
 * @brief Virtual destructor to ensure proper cleanup of derived concrete SaleItem and Decorator classes.
 */

    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~SaleItem() = default;

    /**
     * @brief Calculates the total cost of the sale item
     * @return The cost as a double value
     *
     * This method returns the base cost for concrete components or the
     * decorated cost for decorator classes that add additional charges.
     */
    virtual double cost() = 0;

    /**
     * @brief Generates a description of the sale item
     * @return String describing the item and any decorations applied
     *
     * This method returns a textual description that includes the base item
     * and any additional features added through decorators.
     */
    virtual std::string description() = 0;
};
#endif