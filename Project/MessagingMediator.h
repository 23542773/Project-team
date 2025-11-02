/**
 * @file MessagingMediator.h
 * @brief Defines the abstract base class for the Mediator in the messaging system.
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
 * @brief The abstract interface for a Mediator object, responsible for defining the communication
 * protocol between Colleague objects.
 *
 * Concrete mediators (like ChatMediator) will implement this interface to manage and
 * control the interactions between participants without the participants knowing each other.
 */
class MessagingMediator 
{
public:

/**
 * @brief Virtual destructor to ensure proper cleanup of derived concrete mediator classes.
 */

    virtual ~MessagingMediator() = default;

    /**
     * @brief Sends a message from one Colleague to another.
     *
     * This is a pure virtual function, which concrete mediators must implement to define
     * the specific logic for routing and handling the message.
     *
     * @param from A pointer to the Colleague sending the message.
     * @param to A pointer to the intended recipient Colleague.
     * @param text The content of the message to be sent.
     */

    virtual void sendMessage(Colleague* from, Colleague* to, const std::string& text) = 0;

};

#endif
