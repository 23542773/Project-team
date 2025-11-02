/**
 * @file SalesService.h
 * @brief Sales Service Observer implementation
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * The SalesService class implements the ServiceSubject to manage sales-related events and data.
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
 * @brief Represents a sales receipt
 * @details
 * Contains details about the transaction including success status,
 * order ID, total cost, amount paid, change, and a message.
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
 * @brief Concrete Subject implementation for sales management
 * @details
 * Manages orders and notifies observers of order-related events.
 */
class SalesService : public ServiceSubject
{
public:

	/**
	 * @brief Creates a new Order
	 * @param customerId The ID of the customer placing the order
	 * @param lines The line items in the order
	 * @returns The unique ID of the created order
	 */
	std::string createOrder(std::string customerId, std::vector<events::OrderLine>& lines);

	/**
	 * @brief Assigns an Order to a staff member
	 * @param orderId The unique ID of the order
	 * @param staffId The ID of the staff member to assign
	 * @returns true if the assignment was successful, false otherwise
	 */
  	bool assign(std::string orderId, std::string staffId);

	/**
	 * @brief Updates the status of an Order
	 * @param orderId The unique ID of the order
	 * @param newStatus The new status to set for the order
	 * @returns true if the status update was successful, false otherwise
	 */
  	bool updateStatus(std::string orderId, events::OrderStatus newStatus);

	/**
	 * @brief Gets an Order by its ID
	 * @param orderId The unique ID of the order
	 */
  	std::optional<events::Order> get(std::string orderId);

	/**
	 * @brief Gets the Orders of a staff member
	 * @param staffId The ID of the staff member
	 * @returns A vector of Orders assigned to the specified staff member
	 */
  	std::vector<events::Order> listByStaff(std::string staffId);

	/**
	 * @brief Gets the Orders of a customer
	 * @param customerId The ID of the customer
	 * @returns A vector of Orders associated with the specified customer
	 */
	std::vector<events::Order> getOrdersByCustomer(std::string customerId);

	/**
	 * @brief Gets the Orders assigned to a staff member
	 * @param staffId The ID of the staff member
	 * @returns A vector of Orders assigned to the specified staff member
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
	
	/**
	 * @brief Processes checkout for an order
	 * @param customerId The ID of the customer
	 * @param lines The line items in the order
	 * @param amountPaid The amount paid by the customer
	 * @returns A Receipt containing details of the transaction
	 */
	Receipt checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid);
	
	// Receipt managment
	/**
	 * @brief Retrieves a receipt by order ID
	 * @param orderId The unique ID of the order
	 * @returns An optional Receipt if found, empty otherwise
	 */
	std::optional<Receipt> getReceipt(std::string orderId);

	/**
     * @brief Retrieves a list of all receipts for a specific customer.
     * @param customerId The ID of the customer.
     * @return A vector of Receipt structures associated with the customer.
     */
	
	/**
	 * @brief Retrieves all receipts for a customer
	 * @param customerId The ID of the customer
	 * @returns A vector of Receipts associated with the specified customer
	 */
	std::vector<Receipt> getCustomerReceipts(std::string customerId);

private:

	/**
	 * @brief Generates the next unique order ID
	 * @returns The next order ID as a string
	 */
	std::string nextOrderId();

	/**
	 * @brief Stored orders (orderId -> Order)
	 * @details
	 * This unordered map holds all orders created in the system,
	 * indexed by their unique order IDs.
	 */
 	std::unordered_map<std::string, events::Order> orders;

	/**
	 * @brief Sequence number for generating unique order IDs
     */
  	unsigned long seq = 1;

  	/**
	 * @brief Stored receipts (orderId -> Receipt)
	 */
  	std::unordered_map<std::string, Receipt> receipts;
};

#endif // SALESSERVICE_H