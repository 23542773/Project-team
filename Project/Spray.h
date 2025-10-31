#ifndef SPRAY_H
#define SPRAY_H

#include "Command.h"
#include <vector>
#include <string>

class Plant;

class Spray : public Command 
{

private:
	std::vector<Plant*> plants;
	std::vector<int> previousInsecticide;

public:

	Spray(const std::vector<Plant*>& p);
	void execute() override;
	void undo() override;
	std::string getDescription() const override;
};

#endif
