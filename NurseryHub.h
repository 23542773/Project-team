#ifndef NURSERYHUB_H
#define NURSERYHUB_H
#include "Hub.h"
#include <string>
#include <vector>
#include "Events.h"
#include "SalesService.h"
#include "StaffService.h"
#include "InventoryService.h"
#include "Greenhouse.h"

class NurseryHub : public Hub
{

private:

	/// \brief References to the necessary colleagues and subjects
	StaffService& staff;
	SalesService& sales;
	InventoryService& inv;
	Greenhouse& greenhouse;

public:

	/// \brief Initializes the Hub to contorl communication between the colleagues and observe Greenhouse
	NurseryHub(SalesService& s, InventoryService& i, StaffService& st, Greenhouse& g);

	/// \brief Creates a new order if stock is available and assigns staff 
	void handleNewOrder(std::string customerId, std::vector<events::OrderLine>& lines);

	/// \brief Finishes the order taking out of a reserved state into a finished state
	void completeOrder(std::string orderId);

	/// \brief Cancels an order
	void cancelOrder(std::string orderId);

	/// \brief Responds to events emmitted elsewhere depending on the event
	void onEvent(events::Plant& e);
	void onEvent(events::Order& e);
	void onEvent(events::Stock& e);
};

#endif
