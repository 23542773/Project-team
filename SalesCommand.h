#ifndef SALESCOMMAND_H
#define SALESCOMMAND_H

#include "Command.h"


class SalesService;

class SalesCommand : public Command {

protected:
	SalesService& sales;

public:
	SalesCommand(SalesService& s);
	virtual void execute() = 0;
};

#endif
