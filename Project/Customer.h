/**
 * @file Customer.h
 * @brief Defines the Customer class, a concrete Colleague in the Mediator pattern.
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Colleague.h" // Inherits from the abstract Colleague base class
#include "MessagingMediator.h"
#include "Message.h"
#include <vector>
#include <string>

/**
 * @class Customer
 * @brief Represents a customer entity that can communicate with other colleagues
 * (such as staff) through a MessagingMediator.
 *
 * This class inherits communication capabilities from Colleague and adds
 * specific properties like name and order history.
 */
class Customer : public Colleague
{
private:
    /**
     * @brief A log of all messages received by this customer.
     */
    std::vector<Message> receivedMessages;

public:

    /**
     * @brief The full name of the customer.
     */
    std::string name;

    /**
     * @brief A list of identifiers for orders currently active for this customer.
     */
    std::vector<std::string> activeOrders;

    /**
     * @brief Constructor for the Customer class.
     * @param med A pointer to the central MessagingMediator.
     * @param customerId The unique identifier for this customer (used as the Colleague's userId).
     * @param customerName The full name of the customer.
     */
    Customer(MessagingMediator* med, const std::string& customerId, const std::string& customerName);

    /**
     * @brief Sends a message to another Colleague via the stored mediator.
     * @param to A pointer to the target Colleague (e.g., a Staff member).
     * @param text The content of the message to send.
     */
    void sendMessage(Colleague* to, const std::string& text) override;

    /**
     * @brief Processes and stores an incoming message delivered by the mediator.
     * @param msg The received message structure.
     */
    void receiveMessage(const Message& msg) override;

    /**
     * @brief Retrieves a conversation history between this customer and a specified user.
     *
     * This method filters the `receivedMessages` based on the sender's ID.
     *
     * @param otherUserId The user ID of the other party in the conversation.
     * @return A vector of messages constituting the conversation.
     */
    std::vector<Message> getConversation(const std::string& otherUserId) const;

    /**
     * @brief Gets the unique identifier for this customer (inherited from Colleague's userId).
     * @return The customer's ID string.
     */
    std::string getId() const;
};

#endif