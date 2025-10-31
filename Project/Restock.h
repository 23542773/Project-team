#ifndef RESTOCK_H
#define RESTOCK_H

#include "Command.h"
#include <string>
#include <vector>

class Greenhouse;

class Restock : public Command 
{

private:

	Greenhouse& greenhouse;
	std::string speciesSku;
	int batchSize;
	std::vector<std::string> addedPlantIds;

public:

	Restock(Greenhouse& gh, const std::string& sku, int batch);
	void execute() override;
	void undo() override;
	std::string getDescription() const override;
};

#endif
