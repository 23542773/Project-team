/**
 * @file GiftWrap.h
 * @brief Defines the GiftWrap concrete decorator class
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef GIFTWRAP_H
#define GIFTWRAP_H
#include "SaleDecorator.h"
#include <string>

/**
 * @class GiftWrap
 * @brief Concrete Decorator adding gift wrapping service to sale items
 *
 * This decorator enhances a plant sale item by adding professional gift wrapping,
 * making it suitable for presents and special occasions. The gift wrap includes
 * decorative paper, ribbon, and presentation suitable for gifting.
 *
 * Adds a fixed service charge and updates the description to indicate gift wrapping.
 * Commonly combined with MessageCard decorator for complete gift presentation.
 */
class GiftWrap : public SaleDecorator 
{
public:

    /**
     * @brief Constructs a GiftWrap decorator around an existing SaleItem
     * @param inner Unique pointer to the SaleItem to be decorated
     *
     * Wraps the given sale item and prepares to add gift wrapping features
     * to its cost and description.
     */
    explicit GiftWrap(std::unique_ptr<SaleItem> inner);

    /**
     * @brief Calculates the total cost including the gift wrapping service
     * @return Total cost as a double value (base cost + 25.0)
     *
     * Retrieves the cost from the wrapped component and adds the service
     * charge for professional gift wrapping.
     */
    double cost() override;

    /**
     * @brief Generates description including the gift wrapping service
     * @return String describing the item with " + Gift Wrap" appended
     *
     * Delegates to the wrapped component for the base description and
     * appends text indicating the gift wrapping service.
     */
    std::string description() override;
};
#endif