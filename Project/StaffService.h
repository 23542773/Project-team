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

class MessagingMediator;

class StaffService
{

private:

	/// \brief Maps staffId to Staff
	std::unordered_map<std::string, std::shared_ptr<Staff>> staffMap;

	MessagingMediator* mediator;

public:

	
	StaffService(MessagingMediator* med);

	void setMediator(MessagingMediator* med);

	/// \brief Adds a staff member with a role
	void addStaff(std::string staffId, std::string name, StaffRole role = StaffRole::Sales);

	/// \brief Retrieves the staff member that is the least busy
	std::string leastLoaded();

	/// \brief Assigns an orderId to a Staff member
	void assignOrder(std::string staffId, std::string orderId);

	/// \brief Finishes up an order and relinquishes staff
	void completeOrder(std::string orderId);

	/// \brief Checks if a staff member is available
	bool isAvailable(std::string staffId);

	/// \brief Gets a specific staff member
	Staff* getStaff(std::string staffId);

	/// \brief Gets order linked to a staff member
	std::vector<std::string> getOrdersForStaff(std::string staffId);

	/// \brief Lists all staff members
	std::vector<Staff> listStaff();
};

#endif
