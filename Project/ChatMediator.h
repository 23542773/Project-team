/**
 * @file ChatMediator.h
 * @brief Defines the ChatMediator class, which implements the Mediator pattern
 * to facilitate structured communication between Colleague objects.
 */

#ifndef CHAT_MEDIATOR_H
#define CHAT_MEDIATOR_H

#include <vector>
#include "MessagingMediator.h" // Base class for the mediator

// Forward declarations to avoid circular dependencies and unnecessary includes
class Colleague;
class Staff;

/**
 * @class ChatMediator
 * @brief A concrete mediator that manages communication between various Colleague objects
 * (e.g., customers and staff) in a controlled manner.
 *
 * This class isolates the Colleague objects from knowing about each other, promoting
 * loose coupling in the system. It inherits from MessagingMediator.
 */
class ChatMediator : public MessagingMediator
{
public:

    /**
     * @brief Default constructor for ChatMediator.
     */
    ChatMediator();

    /**
     * @brief Sends a message from one Colleague to another.
     *
     * The implementation of this method defines the specific communication rules
     * (e.g., a customer can only talk to staff, staff can talk to anyone).
     *
     * @param from A pointer to the Colleague sending the message.
     * @param to A pointer to the Colleague receiving the message.
     * @param text The content of the message to be sent.
     */
    void sendMessage(Colleague* from, Colleague* to, const std::string& text) override;

    /**
     * @brief Registers a new Colleague with the mediator, allowing it to participate in communication.
     * @param colleague A pointer to the Colleague to be registered.
     */
    void registerColleague(Colleague* colleague);

    /**
     * @brief Unregisters a Colleague from the mediator, removing it from the active participants.
     * @param colleague A pointer to the Colleague to be unregistered.
     */
    void unregisterColleague(Colleague* colleague);

private:

    /**
     * @brief A list of all Colleague objects currently managed by the mediator.
     */
    std::vector<Colleague*> colleagues;

    /**
     * @brief A sequence number used for message tracking or internal logging.
     * Starts at 1 and is likely incremented with each message/action.
     */
    unsigned long seq = 1;

    /**
     * @brief Utility function to check if a Colleague is a customer.
     * @param colleague A pointer to the Colleague to check.
     * @return true if the colleague is a customer, false otherwise.
     */
    bool isCustomer(Colleague* colleague) const;

    /**
     * @brief Utility function to check if a Colleague is a staff member.
     * @param colleague A pointer to the Colleague to check.
     * @return true if the colleague is a staff member, false otherwise.
     */
    bool isStaff(Colleague* colleague) const;

    /**
     * @brief Utility function to safely cast a Colleague pointer to a Staff pointer.
     * @param colleague A pointer to the Colleague to cast.
     * @return A pointer to the Staff object, or nullptr if the cast is invalid.
     */
    Staff* asStaff(Colleague* colleague) const;
};

#endif