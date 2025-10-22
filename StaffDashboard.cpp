#include "StaffDashboard.h"

void StaffDashboard::onEvent(events::Stock& e)
{
	std::cout << "[Stock] plantId=" << e.plantId << " type=" e.type << "\n";
}

void StaffDashboard::onEvent(events::Order& e)
{
	std::cout 
	<< "[Order] id=" << e.orderId << " type=" << e.type
    << " status=" << e.status << (e.staffId ? " staff="+*e.staffId : "") << "\n";
}

void StaffDashboard::onEvent(events::Plant& e)
{
	std::cout << "[Plant] plantId=" << e.plantId << " type=" << e.type << "\n";
}