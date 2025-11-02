/**
 * @file StaffService.h
 * @brief Defines the StaffService class, responsible for managing staff members, their roles, and their assigned workload.
 */

#ifndef STAFFSERVICE_H
#define STAFFSERVICE_H
#include <string>
#include <climits>
#include <unordered_map>
#include <optional>
#include <vector>
#include <algorithm>
#include <memory>
#include "Staff.h"

// Forward declaration of the mediator class
class MessagingMediator;

/**
 * @class StaffService
 * @brief Manages all staff members, tracking their assignments and facilitating load balancing.
 *
 * This class provides a centralized mechanism for staff-related operations, including
 * adding staff, finding the least busy staff member, and managing order assignments.
 * It also holds a reference to the MessagingMediator for staff communication setup.
 */
class StaffService
{

private:

	/**
     * @brief A map storing all staff objects, indexed by their unique ID.
     * Staff are managed using shared pointers for safe lifetime management.
     */
	std::unordered_map<std::string, std::shared_ptr<Staff>> staffMap;

	/**
     * @brief A pointer to the central MessagingMediator for staff communication.
     */
	MessagingMediator* mediator;

public:

	/**
     * @brief Constructor for StaffService.
     * @param med A pointer to the MessagingMediator to be used by the service.
     */

	
	StaffService(MessagingMediator* med);

	/**
     * @brief Sets or updates the MessagingMediator used by this service.
     * @param med A pointer to the new MessagingMediator.
     */


	void setMediator(MessagingMediator* med);

	/**
     * @brief Creates a new Staff object, registers it in the service, and sets its role.
     * @param staffId The unique identifier for the new staff member.
     * @param name The full name of the new staff member.
     * @param role The functional role of the staff member. Defaults to StaffRole::Sales.
     */

	void addStaff(std::string staffId, std::string name, StaffRole role = StaffRole::Sales);

	/**
     * @brief Finds the ID of the staff member with the fewest currently assigned orders.
     * @return The unique ID of the least loaded staff member, or an empty string if no staff exist.
     */

	std::string leastLoaded();

	/**
     * @brief Assigns a new order ID to a specific staff member's workload.
     * @param staffId The ID of the staff member receiving the assignment.
     * @param orderId The unique ID of the order being assigned.
     */

	void assignOrder(std::string staffId, std::string orderId);

	/**
     * @brief Removes a completed order from a staff member's list of assigned orders.
     * @param orderId The unique ID of the order being completed.
     */

	void completeOrder(std::string orderId);

	/**
     * @brief Checks if a specific staff member is marked as available.
     * @param staffId The ID of the staff member to check.
     * @return true if the staff member is available, false otherwise or if the staff member doesn't exist.
     */

	bool isAvailable(std::string staffId);

	/**
     * @brief Retrieves a specific Staff object by their unique ID.
     * @param staffId The unique identifier of the staff member to retrieve.
     * @return A raw pointer to the requested Staff object, or nullptr if not found.
     */

	Staff* getStaff(std::string staffId);

	/**
     * @brief Retrieves the list of order IDs currently assigned to a staff member.
     * @param staffId The ID of the staff member.
     * @return A vector of order ID strings.
     */

	std::vector<std::string> getOrdersForStaff(std::string staffId);

	/**
     * @brief Retrieves a vector containing copies of all managed Staff objects.
     * @return A vector of Staff objects.
     */
	std::vector<Staff> listStaff();
};

#endif
