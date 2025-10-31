/**
 * @file PlantItem.h
 * @brief Declares the PlantItem class, a concrete SaleItem representing a plant.
 * 
 * Wraps a Plant object and provides cost and description for sale purposes.
 * Supports the Decorator pattern when combined with SaleDecorator subclasses.
 * 
 * @date 2025-10-31
 */

#ifndef PLANTITEM_H
#define PLANTITEM_H

#include "SaleItem.h"
#include "Plant.h"

/**
 * @class PlantItem
 * @brief Concrete SaleItem representing a Plant.
 * 
 * Provides the cost and description of a Plant for sale.
 */
class PlantItem : public SaleItem 
{
public:

    /**
     * @brief Constructs a PlantItem wrapping a Plant pointer.
     * @param p Pointer to the Plant object.
     */
    PlantItem(Plant* p);

    /**
     * @brief Returns the cost of the plant.
     * @return Cost as a double.
     */
    double cost() override;

    /**
     * @brief Returns the description of the plant.
     * @return Description string.
     */
    std::string description() override; 

private:

    /// Pointer to the associated Plant object.
    Plant* plant; 
};

#endif
