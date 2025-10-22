#include "Purchase.h"
#include "SalesService.h"
#include "Events.h"

Purchase::Purchase(SalesService& s, std::string custId, std::vector<events::OrderLine> lines)
	: SalesCommand(s), customerId(custId), orderLines(lines) {
}

void Purchase::execute() {
	sales.createOrder(customerId, orderLines);
}
