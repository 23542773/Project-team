#ifndef WATER_H
#define WATER_H

#include "Command.h"
#include <vector>
#include <string>

class Plant;

class Water : public Command 
{

private:

	std::vector<Plant*> plants;
	std::vector<int> previousMoisture; 

public:

	Water(const std::vector<Plant*>& p);
	void execute() override;
	void undo() override;
	std::string getDescription() const override;
};

#endif
