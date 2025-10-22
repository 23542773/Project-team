#ifndef WATER_H
#define WATER_H

#include "PlantCommand.h"


class Greenhouse;

class Water : public PlantCommand {

public:

	Water(Greenhouse& gh);
	

	void execute() override;
};

#endif
