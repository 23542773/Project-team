/**
 * @file SalesService.h
 * @brief Defines the SalesService class, responsible for order management, status updates,
 * and processing sales transactions, acting as an event Subject.
 */

#ifndef SALESSERVICE_H
#define SALESSERVICE_H
#include "ServiceSubject.h"
#include "Events.h"
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

/**
 * @struct Receipt
 * @brief A data structure encapsulating the result of a checkout transaction.
 */

struct Receipt 
{
/** @brief Indicates whether the transaction was successful. */
    bool success;
    /** @brief The ID of the order associated with this receipt. */
    std::string orderId;
    /** @brief The final total cost of the order. */
    double totalCost;
    /** @brief The amount of money provided by the customer. */
    double amountPaid;
    /** @brief The change due back to the customer. */
    double change;
    /** @brief A descriptive message about the transaction status. */
    std::string message;
};

/**
 * @class SalesService
 * @brief Manages the lifecycle of customer orders and acts as the **ServiceSubject**
 * to notify observers of Order events.
 *
 * It provides methods for creating, assigning, and updating orders, as well as handling the
 * final checkout process.
 */

class SalesService : public ServiceSubject
{
public:

/**
 * @brief Creates a new Order, registers it in the system, and notifies all observers of the `Created` event.
 * @param customerId The ID of the customer placing the order.
 * @param lines A vector of OrderLine structures detailing the items ordered.
 * @return The unique ID of the newly created order.
 */

	std::string createOrder(std::string customerId, std::vector<events::OrderLine>& lines);

	/**
     * @brief Assigns a staff member to an existing order and notifies observers of the `Assigned` event.
     * @param orderId The unique ID of the order to assign.
     * @param staffId The ID of the staff member being assigned.
     * @return true if the assignment was successful, false if the order does not exist.
     */

  	bool assign(std::string orderId, std::string staffId);

	/**
     * @brief Updates the status of an existing order and notifies observers of the status change event.
     * @param orderId The unique ID of the order to update.
     * @param newStatus The new status to set (e.g., InProgress, Completed, Cancelled).
     * @return true if the status update was successful, false if the order does not exist.
     */

  	bool updateStatus(std::string orderId, events::OrderStatus newStatus);

	/**
     * @brief Retrieves an Order object by its ID.
     * @param orderId The unique ID of the order.
     * @return An `std::optional` containing the Order structure if found, or an empty optional otherwise.
     */

  	std::optional<events::Order> get(std::string orderId);

	/**
     * @brief Retrieves a list of all orders currently assigned to a specific staff member.
     * @param staffId The ID of the staff member.
     * @return A vector of Order structures assigned to the staff member.
     * @deprecated Use `getOrdersByStaff` instead for clarity.
     */

  	std::vector<events::Order> listByStaff(std::string staffId);

	/**
     * @brief Retrieves a list of all orders placed by a specific customer.
     * @param customerId The ID of the customer.
     * @return A vector of Order structures associated with the customer.
     */

	std::vector<events::Order> getOrdersByCustomer(std::string customerId);

	/**
     * @brief Retrieves a list of all orders currently assigned to a specific staff member.
     * @param staffId The ID of the staff member.
     * @return A vector of Order structures assigned to the staff member.
     */

	std::vector<events::Order> getOrdersByStaff(std::string staffId);

	/**
     * @brief Processes a sales transaction, including order creation, calculating cost, and processing payment.
     *
     * This method creates an order, calculates the total cost based on the lines, processes the payment,
     * stores a receipt, and notifies observers of the outcome.
     *
     * @param customerId The ID of the customer making the purchase.
     * @param lines A vector of OrderLine structures detailing the items being purchased.
     * @param amountPaid The monetary amount provided by the customer.
     * @return A Receipt structure detailing the outcome of the transaction.
     */
	
	Receipt checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid);
	
	/**
     * @brief Retrieves a stored receipt by its associated order ID.
     * @param orderId The unique ID of the order.
     * @return An `std::optional` containing the Receipt structure if found, or an empty optional otherwise.
     */

	std::optional<Receipt> getReceipt(std::string orderId);

	/**
     * @brief Retrieves a list of all receipts for a specific customer.
     * @param customerId The ID of the customer.
     * @return A vector of Receipt structures associated with the customer.
     */
	
	std::vector<Receipt> getCustomerReceipts(std::string customerId);

private:

/**
 * @brief Generates the next sequential unique order ID string.
 * @return The next available order ID.
 */

	std::string nextOrderId();

	/**
     * @brief A map storing all active and historical orders, keyed by the unique order ID.
     */

 	std::unordered_map<std::string, events::Order> orders;

	/**
     * @brief A sequence counter used to generate unique order IDs.
     */

  	unsigned long seq = 1;
  	
  	/**
     * @brief A map storing transaction receipts, keyed by the associated order ID.
     */
  	std::unordered_map<std::string, Receipt> receipts;
};

#endif
