#ifndef STAFFSERVICE_H
#define STAFFSERVICE_H
#include <string>
#include <climits>
#include <unordered_map>
#include <optional>
#include <vector>
#include <algorithm>
#include "ServiceColleague.h"
#include "Staff.h"

class StaffService : public ServiceColleague
{

private:

	/// \brief Maps staffId to Staff
	std::unordered_map<string, Staff> staffMap;

public:

	/// \brief Adds a staff member
	void addStaff(std::string staffId, std::string name);

	/// \brief Retrieves the staff member that is the least busy
	std::string leastLoaded();

	/// \brief Assigns an orderId to a Staff member
	void assignOrder(std::string staffId, std::string orderId);

	/// \brief Finishes up an order and relinquishes staff
	void completeOrder(std::string orderId);

	/// \brief Checks if a staff member is available
	bool isAvailable(std::string staffId);

	/// \brief Gets a specific staff member
	Staff* get(std::string staffId);

	/// \brief Gets order linked to a staff member
	std::vector<std::string> getOrdersForStaff(std::string staffId);

	/// \brief Lists all staff members
	std::vector<Staff> listStaff();
};

#endif
