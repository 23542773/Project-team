#ifndef FERTILIZE_H
#define FERTILIZE_H

#include "Command.h"
#include <vector>
#include <string>

class Plant;

class Fertilize : public Command 
{

private:

	std::vector<Plant*> plants;
	std::vector<int> previousHealth;

public:

	Fertilize(const std::vector<Plant*>& p);	
	void execute() override;
	void undo() override;
	std::string getDescription() const override;
};

#endif
