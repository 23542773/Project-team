#ifndef SALESSERVICE_H
#define SALESSERVICE_H
#include "ServiceSubject.h"
#include "Events.h"
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

struct Receipt 
{
	bool success;
	std::string orderId;
	double totalCost;
	double amountPaid;
	double change;
	std::string message;
};

class SalesService : public ServiceSubject
{
public:

	/// \brief Creates the Order and notifies dependents
	std::string createOrder(std::string customerId, std::vector<events::OrderLine>& lines);

	/// \brief Assigns a staffId to an Order
  	bool assign(std::string orderId, std::string staffId);

	/// \brief Updates the Status of an Order
  	bool updateStatus(std::string orderId, events::OrderStatus newStatus);

	/// \brief Gets the Order associated with an id
  	std::optional<events::Order> get(std::string orderId);

	/// \brief Gets the Orders of a staff member
  	std::vector<events::Order> listByStaff(std::string staffId);

	std::vector<events::Order> getOrdersByCustomer(std::string customerId);

	std::vector<events::Order> getOrdersByStaff(std::string staffId);
	
	Receipt checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid);
	
	// Receipt management
	std::optional<Receipt> getReceipt(std::string orderId);
	
	std::vector<Receipt> getCustomerReceipts(std::string customerId);

private:

	/// \brief Assigns Order Number
	std::string nextOrderId();

	/// \brief Map of staffId to Orders
 	std::unordered_map<std::string, events::Order> orders;

	/// \brief Tracks Order Number
  	unsigned long seq = 1;
  	
  	/// \brief Stored receipts (orderId -> Receipt)
  	std::unordered_map<std::string, Receipt> receipts;
};

#endif
