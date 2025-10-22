#ifndef PURCHASE_H
#define PURCHASE_H

#include "SalesCommand.h"
#include <string>
#include <vector>


class SalesService;
namespace events {
	struct OrderLine;
}


class Purchase : public SalesCommand {

private:
	std::string customerId;
	std::vector<events::OrderLine> orderLines;

public:

	Purchase(SalesService& s, std::string custId, std::vector<events::OrderLine> lines);
	void execute() override;
};

#endif
