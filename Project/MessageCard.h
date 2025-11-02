/**
 * @file MessageCard.h
 * @brief Defines the MessageCard decorator, which adds a customizable message card
 * and associated cost to a SaleItem.
 */

#ifndef MESSAGECARD_H
#define MESSAGECARD_H
#include "SaleDecorator.h"
#include <string>

/**
 * @class MessageCard
 * @brief A concrete Decorator that wraps a SaleItem, adding the responsibility and cost
 * for including a personalized message card.
 *
 * It composes an existing SaleItem (via SaleDecorator) and modifies its cost and description
 * while keeping the inner component structure intact.
 */

class MessageCard : public SaleDecorator 
{
public:

/**
 * @brief Constructor for the MessageCard decorator.
 * @param inner A unique pointer to the SaleItem object being decorated.
 * @param msg The personalized message text to be included on the card.
 */

    explicit MessageCard(std::unique_ptr<SaleItem> inner, std::string msg);
    /**
     * @brief Calculates the total cost, which is the base item's cost plus the cost of the message card.
     * @return The combined cost of the item and the message card service.
     */

    double cost() override;
    /**
     * @brief Provides a description of the item, including the personalized message card service.
     * @return A string combining the inner item's description with a note about the message card.
     */
    std::string description() override;

private:
/**
 * @brief The personalized message text to be printed on the card.
 */

    std::string msg;
};
#endif