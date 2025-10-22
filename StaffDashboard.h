#ifndef STAFFDASHBOARD_H
#define STAFFDASHBOARD_H
#include <iostream>
#include "NurseryObserver.h"

class StaffDashboard : public NurseryObserver
{

public:

	/// \brief Notifies staff dashboard of Stock Event
	void onEvent(events::Stock& e);

	/// \brief Notifies staff dashboard of an Order Event
	void onEvent(events::Order& e);

	/// \brief Notifies staff dashboard of Plant Event
	void onEvent(events::Plant& e);

};

#endif
