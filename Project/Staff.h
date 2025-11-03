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
#include <algorithm>


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
    PlantCare,       ///< Staff responsible for plant maintenance and care
    Inventory,       ///< Staff managing stock and inventory operations
    Sales            ///< Staff handling customer interactions and sales
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

private:

    /// Messages the Staff member receives
    std::vector<Message> receivedMessages;

     /// Staff member's display name
    std::string name;

    /// List of order IDs currently assigned to this staff member
    std::vector<std::string> assignedOrders;

    /// Availability status for order assignment
    bool available = true;

    /// Role determining communication permissions and responsibilities
    StaffRole role;

public:

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
     * @param toUserId String of the other colleague
     * @param text The message content to send
     *
     * Routes the message through the mediator. The mediator will enforce
     * role-based communication rules (e.g., PlantCare cannot message Customers).
     */
    void sendMessage(const std::string& toUserId, const std::string& text) override;

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
    /**
     * @brief Gets the staff member's display name
     * @return std::string containing the staff member's name
     */
    std::string getName() const;

    /**
     * @brief Returns the list of order IDs currently assigned to this staff member
     * @return Const reference to a vector of order ID strings
     *
     * The returned reference is to an internal container and should not be
     * modified by the caller. Use addAssignedOrder/removeAssignedOrder to
     * update assignments.
     */
    const std::vector<std::string>& getAssignedOrders() const;

    /**
     * @brief Checks whether the staff member is available for new assignments
     * @return true if the staff member is available, false otherwise
     */
    bool isAvailable() const;

    /**
     * @brief Adds an order ID to the staff member's assigned orders
     * @param orderId The ID of the order to assign
     *
     * If the order ID is already present in the list this function does nothing.
     */
    void addAssignedOrder(const std::string& orderId);

    /**
     * @brief Removes an order ID from the staff member's assigned orders
     * @param orderId The ID of the order to remove
     *
     * If the order ID is not found this function does nothing.
     */
    void removeAssignedOrder(const std::string& orderId);
    
    /**
     * @brief Sets the availability status for the staff member
     * @param avail True to mark as available, false to mark as unavailable
     */
    void setAvailable(bool avail);
};

#endif
