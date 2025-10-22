#ifndef PLANTCOMMAND_H
#define PLANTCOMMAND_H

#include "Command.h"


class Greenhouse;

class PlantCommand : public Command {

protected:
	Greenhouse& greenhouse;

public:

	PlantCommand(Greenhouse& gh);
	

	virtual void execute() = 0;
};

#endif
