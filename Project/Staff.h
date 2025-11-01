/**
 * @file Staff.h
 * @brief Defines the Staff concrete colleague class and StaffRole enumeration
 * @date 2025-10-31
 * @author Project Teams
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
 * @brief Enumeration defining different roles for staff members
 *
 * Staff roles determine communication permissions enforced by the ChatMediator:
 * - PlantCare: Can communicate with Inventory staff
 * - Inventory: Can communicate with PlantCare and Sales staff
 * - Sales: Can communicate with Customers, other Sales staff, and Inventory staff
 */
enum class StaffRole 
{
    PlantCare,   ///< Staff responsible for plant maintenance and care
    Inventory,   ///< Staff managing stock and inventory operations
    Sales        ///< Staff handling customer interactions and sales
};

/**
 * @class Staff
 * @brief Concrete Colleague representing a nursery staff member
 *
 * This class represents staff members in the nursery system who can communicate
 * with customers and other staff through the mediator. Staff members have assigned
 * roles that determine their communication permissions as enforced by ChatMediator.
 *
 * Staff members maintain their message history, track assigned orders, and have
 * an availability status. All communication is mediated to enforce business rules
 * about inter-departmental and customer communication.
 */
class Staff : public Colleague 
{

public:

    /// Staff member's display name
    std::string name;

    /// List of order IDs currently assigned to this staff member
    std::vector<std::string> assignedOrders;

    /// Availability status for order assignment
    bool available = true;

    /// Role determining communication permissions and responsibilities
    StaffRole role;

    /**
     * @brief Constructs a Staff colleague with a specific role
     * @param med Pointer to the MessagingMediator for communication
     * @param staffId Unique identifier for this staff member
     * @param staffName Display name for this staff member
     * @param staffRole The role assigned to this staff member (default: Sales)
     *
     * Creates a staff member who can communicate through the mediator based on
     * their role permissions and manages their assigned orders.
     */
    Staff(MessagingMediator* med, const std::string& staffId, const std::string& staffName, StaffRole staffRole = StaffRole::Sales);

    /**
     * @brief Sends a message to a colleague
     * @param to Pointer to the recipient Colleague
     * @param text The message content to send
     *
     * Routes the message through the mediator. The mediator will enforce
     * role-based communication rules (e.g., PlantCare cannot message Customers).
     */
    void sendMessage(Colleague* to, const std::string& text);

    /**
     * @brief Receives a message from the mediator
     * @param msg The Message object to receive
     *
     * Stores the received message in the staff member's message history for
     * later retrieval and display in conversations.
     */
    void receiveMessage(const Message& msg) override;

    /**
     * @brief Retrieves conversation history with another user
     * @param otherUserId User ID of the other party in the conversation
     * @return Vector of Message objects representing the conversation
     *
     * Filters the staff member's message history to return only messages
     * sent to or received from the specified user.
     */
    std::vector<Message> getConversation(const std::string& otherUserId) const;

    /**
     * @brief Gets the staff member's unique ID
     * @return String containing the staff ID
     */
    std::string getId() const;

    /**
     * @brief Gets the staff member's role
     * @return StaffRole enumeration value
     */
    StaffRole getRole() const;

private:

    /// Collection of all messages received by this staff member
    std::vector<Message> receivedMessages;
};

#endif
