#ifndef SALESSERVICE_H
#define SALESSERVICE_H
#include "ServiceSubject.h"
#include "ServiceColleague.h"
#include "Events.h"
#include <string>
#include <unordered_map>
#include <optional>
#include <vector>

class SalesService : public ServiceSubject, public ServiceColleague
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
  	std::vector<events::Order> listByStaff(std::string staffId) ;

private:

	/// \brief Assigns Order Number
	std::string nextOrderId();

	/// \brief Map of staffId to Orders
 	std::unordered_map<std::string, events::Order> orders;

	/// \brief Tracks Order Number
  	unsigned long seq = 1;
};

#endif
