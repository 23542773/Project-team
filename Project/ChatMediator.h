/**
 * @file ChatMediator.h
 * @brief Defines the ChatMediator concrete mediator class
 * @date 2025-10-31
 * @author Project Teams
 */

#ifndef CHAT_MEDIATOR_H
#define CHAT_MEDIATOR_H
#include <vector>
#include <unordered_map>
#include "MessagingMediator.h"

class Colleague;
class Staff;

/**
 * @class ChatMediator
 * @brief Concrete Mediator implementing communication rules between Staff and Customers
 *
 * This class implements the Mediator pattern by managing all messaging between
 * colleagues in the nursery system. It enforces business rules about who can
 * communicate with whom based on staff roles and user types.
 *
 * Communication Rules:
 * - Customers can only message Sales Staff
 * - Sales Staff can message Customers, other Sales Staff, and Inventory Staff
 * - Plant Care Staff can message Inventory Staff
 * - Inventory Staff can message Plant Care and Sales Staff
 *
 * The mediator maintains a registry of all colleagues and routes messages between
 * them while enforcing these constraints, preventing unauthorized communication.
 */
class ChatMediator : public MessagingMediator 
{
public:

    /**
     * @brief Constructs a ChatMediator with empty colleague registry
     *
     * Initializes the mediator with no registered colleagues and a message
     * sequence counter starting at 1.
     */
    ChatMediator();

    /**
     * @brief Sends a message from one colleague to another by user ID
     * @param from Pointer to the Colleague sending the message
     * @param toUserId String ID of the recipient colleague
     * @param text The message content to send
     *
     * Routes the message through the mediator, applying business rules to
     * determine if the communication is allowed before delivery.
     */
    void sendMessageToId(Colleague* from, const std::string& toUserId, const std::string& text) override;

    /**
     * @brief Registers a colleague with the mediator
     * @param colleague Pointer to the Colleague to register
     *
     * Adds the colleague to the mediator's registry, enabling it to send
     * and receive messages through the mediator.
     */
    void registerColleague(Colleague* colleague);

    /**
     * @brief Unregisters a colleague from the mediator
     * @param colleague Pointer to the Colleague to unregister
     *
     * Removes the colleague from the mediator's registry, preventing further
     * message routing to or from this colleague.
     */
    void unregisterColleague(Colleague* colleague);

private:

    /// Collection of all registered colleagues
    std::vector<Colleague*> colleagues;

    /// Index mapping user IDs to colleague pointers for fast lookup
    std::unordered_map<std::string, Colleague*> indexById;

    /// Message sequence number for generating unique message IDs
    unsigned long seq = 1;

    /**
     * @brief Internal method to send message between two colleagues
     * @param from Pointer to the sending Colleague
     * @param to Pointer to the receiving Colleague
     * @param text The message content
     *
     * Performs the actual message delivery after validating communication rules,
     * creates Message objects, and delivers to both sender and recipient for
     * conversation history tracking.
     */
    void sendMessage(Colleague* from, Colleague* to, const std::string& text);

    /**
     * @brief Checks if a colleague is a Customer
     * @param colleague Pointer to the Colleague to check
     * @return True if the colleague is a Customer, false otherwise
     */
    bool isCustomer(Colleague* colleague) const;

    /**
     * @brief Checks if a colleague is a Staff member
     * @param colleague Pointer to the Colleague to check
     * @return True if the colleague is a Staff member, false otherwise
     */
    bool isStaff(Colleague* colleague) const;

    /**
     * @brief Casts a colleague to Staff pointer
     * @param colleague Pointer to the Colleague to cast
     * @return Staff pointer if the cast succeeds, nullptr otherwise
     */
    Staff* asStaff(Colleague* colleague) const;
};

#endif
