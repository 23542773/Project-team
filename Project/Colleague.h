/**
 * @file Colleague.h
 * @brief Defines the abstract Colleague base class for the Mediator pattern
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef COLLEAGUE_H
#define COLLEAGUE_H

#include <string>

class MessagingMediator;
struct Message;

/**
 * @class Colleague
 * @brief Abstract Colleague class in the Mediator pattern representing communicating entities
 *
 * This class defines the interface for all colleagues that communicate through a mediator
 * in the nursery system. Colleagues do not communicate directly with each other; instead,
 * they send messages through the MessagingMediator.
 *
 * This design promotes loose coupling by preventing colleagues from referencing each other
 * explicitly, making it easier to modify communication rules and add new colleague types.
 */
class Colleague 
{
protected:

    /// Pointer to the mediator that handles message routing
    MessagingMediator* mediator;

    /// Unique identifier for this colleague
    std::string userId;

public:

    /**
     * @brief Constructs a Colleague with a mediator and user ID
     * @param med Pointer to the MessagingMediator for communication
     * @param id Unique identifier for this colleague
     *
     * Initializes the colleague with access to the mediator through which
     * all communication will be routed.
     */
    Colleague(MessagingMediator* med, const std::string& id) : mediator(med), userId(id) {}
    
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~Colleague() = default;

    /**
     * @brief Sends a message to another colleague by user ID
     * @param toUserId String ID of the recipient colleague
     * @param text The message content to send
     *
     * Delegates to the mediator to route the message, allowing the mediator
     * to enforce communication rules and business logic.
     */
    virtual void sendMessage(const std::string& toUserId, const std::string& text) = 0;

    /**
     * @brief Receives a message from the mediator
     * @param msg The Message object containing message details
     *
     * Called by the mediator when a message is being delivered to this colleague.
     * Concrete colleagues implement this to store or process received messages.
     */
    virtual void receiveMessage(const Message& msg) = 0;

    /**
     * @brief Gets the unique user ID of this colleague
     * @return String containing the user ID
     */
    std::string getUserId() const { return userId; }
};

#endif
