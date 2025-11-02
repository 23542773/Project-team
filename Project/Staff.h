/**
 * @file Staff.h
 * @brief Defines the Staff class, a concrete Colleague representing a staff member in the Mediator pattern.
 */

#ifndef STAFF_H
#define STAFF_H

#include "Colleague.h"
#include "MessagingMediator.h"
#include "Message.h"
#include <vector>
#include <string>

/**
 * @enum StaffRole
 * @brief Enumeration of the different functional roles a staff member can have.
 */



enum class StaffRole 
{
/** @brief Role focused on the maintenance and care of plants (e.g., in the Greenhouse). */
    PlantCare,
    /** @brief Role focused on managing stock levels and plant disposition (e.g., in the InventoryService). */
    Inventory,
    /** @brief Role focused on order fulfillment and customer transactions (e.g., in the SalesService). */
    Sales        
};


/**
 * @class Staff
 * @brief Represents a staff entity that can communicate with other colleagues (customers, other staff)
 * through a central MessagingMediator.
 *
 * This class extends the basic Colleague functionality with specific staff properties like role,
 * availability, and assigned orders.
 */

class Staff : public Colleague 
{

public:
    /**
     * @brief The full name of the staff member.
     */

    std::string name;

    /**
     * @brief A list of identifiers for orders currently assigned to this staff member.
     */

    std::vector<std::string> assignedOrders;

    /**
     * @brief Flag indicating if the staff member is currently available to take on new tasks or chats. Defaults to true.
     */

    bool available = true;

    /**
     * @brief The functional role of the staff member within the system.
     */

    StaffRole role;

    /**
     * @brief Constructor for the Staff class.
     * @param med A pointer to the central MessagingMediator.
     * @param staffId The unique identifier for this staff member (used as the Colleague's userId).
     * @param staffName The full name of the staff member.
     * @param staffRole The specific role of the staff member. Defaults to StaffRole::Sales.
     */

    Staff(MessagingMediator* med, const std::string& staffId, const std::string& staffName, StaffRole staffRole = StaffRole::Sales);

    /**
     * @brief Sends a message to another Colleague via the stored mediator.
     * @param to A pointer to the target Colleague (e.g., a Customer or another Staff member).
     * @param text The content of the message to send.
     */

    void sendMessage(Colleague* to, const std::string& text);

    /**
     * @brief Processes and stores an incoming message delivered by the mediator.
     * @param msg The received message structure.
     */

    void receiveMessage(const Message& msg) override;

    /**
     * @brief Retrieves a conversation history between this staff member and a specified user.
     *
     * Filters received messages based on the sender's ID.
     *
     * @param otherUserId The user ID of the other party in the conversation.
     * @return A vector of messages constituting the conversation.
     */

    std::vector<Message> getConversation(const std::string& otherUserId) const;

    /**
     * @brief Gets the unique identifier for this staff member (inherited from Colleague's userId).
     * @return The staff member's ID string.
     */

    std::string getId() const;

    /**
     * @brief Gets the functional role of the staff member.
     * @return The StaffRole enumeration value.
     */

    StaffRole getRole() const;

private:

/**
 * @brief A log of all messages received by this staff member.
 */

    std::vector<Message> receivedMessages;
};

#endif
