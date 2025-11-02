/**
 * @file Colleague.h
 * @brief Defines the abstract base class Colleague, a participant in the Mediator pattern.
 */

#ifndef COLLEAGUE_H
#define COLLEAGUE_H

#include <string>

// Forward declarations to minimize dependencies
class MessagingMediator;
struct Message;

/**
 * @class Colleague
 * @brief An abstract base class representing a component that interacts with other
 * components through a central MessagingMediator.
 *
 * Colleague classes decouple communication logic by delegating interactions to the
 * mediator instead of communicating directly with each other.
 */
class Colleague
{
protected:

    /**
     * @brief A pointer to the central mediator object.
     * All communication from this Colleague goes through the mediator.
     */
    MessagingMediator* mediator;

    /**
     * @brief A unique identifier for this colleague.
     */
    std::string userId;

public:
    /**
     * @brief Constructor for the Colleague class.
     * @param med A pointer to the MessagingMediator that will manage this colleague's communications.
     * @param id A unique string identifier for this colleague.
     */
    Colleague(MessagingMediator* med, const std::string& id) : mediator(med), userId(id) {}

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~Colleague() = default;

    /**
     * @brief Sends a message to a specific Colleague via the mediator.
     *
     * This is a pure virtual function and must be implemented by concrete subclasses.
     * The implementation will typically call a method on the stored 'mediator'.
     *
     * @param to A pointer to the target Colleague.
     * @param text The content of the message.
     */
    virtual void sendMessage(Colleague* to, const std::string& text) = 0;

    /**
     * @brief Receives a message that was delivered by the mediator.
     *
     * This is a pure virtual function and must be implemented by concrete subclasses
     * to define how the colleague reacts to incoming messages.
     *
     * @param msg The received message structure.
     */
    virtual void receiveMessage(const Message& msg) = 0;

    /**
     * @brief Getter for the colleague's user ID.
     * @return The unique string identifier of this colleague.
     */
    std::string getUserId() const { return userId; }
};

#endif