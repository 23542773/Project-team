/**
 * @file Customer.h
 * @brief Defines the Customer concrete colleague class
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Colleague.h"
#include "MessagingMediator.h"
#include "Message.h"
#include <vector>
#include <string>

/**
 * @class Customer
 * @brief Concrete Colleague representing a nursery customer
 *
 * This class represents customers in the nursery system who can communicate
 * with staff members through the mediator. Customers can only send messages
 * to Sales Staff due to business rules enforced by the ChatMediator.
 *
 * Customers maintain their own message history and track their active orders.
 * All communication is routed through the mediator to maintain loose coupling
 * and enforce organizational communication policies.
 */

class Customer : public Colleague 
{
private:

    /// Collection of all messages received by this customer
    std::vector<Message> receivedMessages;

    /// Customer's display name
    std::string name;

    /// List of active order IDs for this customer
    std::vector<std::string> activeOrders;

public:

    /**
     * @brief Constructs a Customer colleague
     * @param med Pointer to the MessagingMediator for communication
     * @param customerId Unique identifier for this customer
     * @param customerName Display name for this customer
     *
     * Creates a customer who can communicate through the mediator and
     * maintains their own message history and order list.
     */
    Customer(MessagingMediator* med, const std::string& customerId, const std::string& customerName);

    /**
     * @brief Sends a message to a colleague by user ID
     * @param toUserId The recipient colleague's user ID
     * @param text The message content to send
     *
     * Routes the message through the mediator. The mediator will enforce
     * rules restricting customers to only message Sales Staff.
     */
    void sendMessage(const std::string& toUserId, const std::string& text) override;

    /**
     * @brief Receives a message from the mediator
     * @param msg The Message object to receive
     *
     * Stores the received message in the customer's message history for
     * later retrieval and display in conversations.
     */
    void receiveMessage(const Message& msg) override;

    /**
     * @brief Retrieves conversation history with another user
     * @param otherUserId User ID of the other party in the conversation
     * @return Vector of Message objects representing the conversation
     *
     * Filters the customer's message history to return only messages
     * sent to or received from the specified user.
     */
    std::vector<Message> getConversation(const std::string& otherUserId) const;

    /**
     * @brief Gets the customer's unique ID
     * @return String containing the customer ID
     */
    std::string getId() const;

    /**
     * @brief Gets the customer's display name
     */
    std::string getName() const;

    /**
     * @brief Get active orders for this customer
     */
    const std::vector<std::string>& getActiveOrders() const;

    /**
     * @brief Add an active order ID
     */
    void addActiveOrder(const std::string& orderId);
};

#endif
