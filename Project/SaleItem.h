/**
 * @file SaleItem.h
 * @brief Defines the abstract base component interface for the Decorator design pattern.
 */

#ifndef SALEITEM_H
#define SALEITEM_H
#include <memory>
#include <string>
#include "Plant.h"

/**
 * @class SaleItem
 * @brief The abstract Component interface for objects that can be sold, defining core operations.
 *
 * Both simple sale items (like a single Plant) and decorated items must implement this interface.
 * It is the basis for the Decorator pattern, allowing costs and descriptions to be
 * dynamically added and chained.
 */

class SaleItem 
{
public:
/**
 * @brief Virtual destructor to ensure proper cleanup of derived concrete SaleItem and Decorator classes.
 */

    virtual ~SaleItem() = default;

    /**
     * @brief Calculates the total cost of the sale item, including any decorations.
     *
     * This is a pure virtual function and must be implemented by all concrete components and decorators.
     *
     * @return The total cost as a double.
     */

    virtual double cost() = 0;

    /**
     * @brief Provides a detailed description of the sale item, including any added decorations.
     *
     * This is a pure virtual function and must be implemented by all concrete components and decorators.
     *
     * @return A string containing the descriptive text.
     */
    
    virtual std::string description() = 0;
};
#endif