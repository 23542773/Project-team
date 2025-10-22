#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>

/// \brief Staff struct containing all info pertaining to a Staff member.
struct Staff 
{
	std::string staffId;
	std::string name;
	std::vector<std::string> assignedOrders;
    bool available = true;
	//Role still needed to be added
};

#endif
