#ifndef RESTOCK_H
#define RESTOCK_H

#include "PlantCommand.h"


class Greenhouse;

class Restock : public PlantCommand {
	Restock(Greenhouse& gh);

	void execute() override;
};

#endif
