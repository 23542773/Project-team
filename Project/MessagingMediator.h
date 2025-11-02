/**
 * @file MessagingMediator.h
 * @brief Defines the abstract Mediator interface for the Mediator pattern
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef MESSAGING_MEDIATOR_H
#define MESSAGING_MEDIATOR_H
#include <string>
#include <vector>
#include "Message.h"

// Forward declaration of the Colleague abstract class
class Colleague;

/**
 * @class MessagingMediator
 * @brief Abstract Mediator class in the Mediator pattern for inter-colleague communication
 *
 * This class defines the interface for mediating communication between Colleague objects
 * in the nursery system. It implements the Mediator pattern by providing a centralized
 * point of communication that decouples colleagues from each other.
 *
 * The mediator encapsulates how colleagues interact, allowing communication logic and
 * business rules to be centralized rather than distributed across colleague objects.
 */
class MessagingMediator 
{
public:

    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~MessagingMediator() = default;

    /**
     * @brief Sends a message from one colleague to another identified by user ID
     * @param from Pointer to the Colleague sending the message
     * @param toUserId String ID of the recipient colleague
     * @param text The message content to send
     *
     * This method routes messages between colleagues without requiring them to
     * know about each other directly, maintaining loose coupling in the system.
     */
    virtual void sendMessageToId(Colleague* from, const std::string& toUserId, const std::string& text) = 0;

};

#endif
