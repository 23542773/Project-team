/**
 * @file GiftWrap.h
 * @brief Defines the GiftWrap decorator, which adds gift wrapping functionality and cost to a SaleItem.
 */

#ifndef GIFTWRAP_H
#define GIFTWRAP_H

#include "SaleDecorator.h" // Inherits from the abstract decorator base
class GiftWrap : public SaleDecorator 
{
public:

    /**
     * @brief Constructor for the GiftWrap decorator.
     * @param inner A unique pointer to the SaleItem object being wrapped.
     */
    explicit GiftWrap(std::unique_ptr<SaleItem> inner);

    /**
     * @brief Calculates the total cost, which is the base item's cost plus the cost of the gift wrap.
     * @return The combined cost of the item and the gift wrap service.
     */
    double cost() override;

    /**
     * @brief Provides a description of the item, including the added gift wrap.
     * @return A string combining the inner item's description with a note about the gift wrap.
     */
    std::string description() override;
};
#endif