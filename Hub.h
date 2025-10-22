#ifndef HUB_H
#define HUB_H
#include "Events.h"
class Hub
{
    virtual ~Hub() = default;

    /// \brief Handles new order, delegates to subclass
    virtual void handleNewOrder(std::string customerId, std::vector<events::OrderLine>& lines) = 0;

    /// \brief Completes an order, delegates to subclass
    virtual void completeOrder(std::string orderId) = 0;

    /// \brief Cancels an order, delegates to subclass
    virtual void cancelOrder(std::string orderId) = 0;
};
#endif