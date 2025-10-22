#ifndef FETILIZE_H
#define FETILIZE_H

#include "PlantCommand.h"


class Greenhouse;

class Fetilize : public PlantCommand {

public:
	Fetilize(Greenhouse& gh);
	void execute() override;
};

#endif
