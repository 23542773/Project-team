/**
 * @file MessageCard.h
 * @brief Defines the MessageCard concrete decorator class
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef MESSAGECARD_H
#define MESSAGECARD_H
#include "SaleDecorator.h"
#include <string>

/**
 * @class MessageCard
 * @brief Concrete Decorator adding personalized message card to sale items
 *
 * This decorator enhances a plant sale item by including a personalized greeting
 * card with a custom message. The card allows customers to add a personal touch
 * to their plant gifts with messages for birthdays, celebrations, or special occasions.
 *
 * Stores the customer's message and adds both a service charge and the message text
 * to the item description. Often combined with GiftWrap for complete gift presentation.
 */
class MessageCard : public SaleDecorator 
{
public:

    /**
     * @brief Constructs a MessageCard decorator with a personalized message
     * @param inner Unique pointer to the SaleItem to be decorated
     * @param msg The personalized message to include on the card
     *
     * Wraps the given sale item and stores the custom message that will be
     * printed on the greeting card accompanying the plant.
     */
    explicit MessageCard(std::unique_ptr<SaleItem> inner, std::string msg);

    /**
     * @brief Calculates the total cost including the message card service
     * @return Total cost as a double value (base cost + 15.0)
     *
     * Retrieves the cost from the wrapped component and adds the service
     * charge for the personalized message card.
     */
    double cost() override;

    /**
     * @brief Generates description including the message card and its text
     * @return String describing the item with " + Card(message)" appended
     *
     * Delegates to the wrapped component for the base description and
     * appends text indicating the message card service along with the
     * actual message content in parentheses.
     */
    std::string description() override;

private:
/**
 * @brief The personalized message text to be printed on the card.
 */

    /// The personalized message to be printed on the greeting card
    std::string msg;
};
#endif