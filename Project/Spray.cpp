#include "Spray.h"
#include "Plant.h"
#include <iostream>
#include <sstream>

Spray::Spray(const std::vector<Plant*>& p) : plants(p) {}

void Spray::execute() 
{
	previousInsecticide.clear();
	previousInsecticide.reserve(plants.size());
	
	for (Plant* p : plants) 
	{
		if (p) 
		{
			previousInsecticide.push_back(p->getInsecticide());
			p->sprayInsecticide();
		}
	}
}

void Spray::undo() 
{
	for (size_t i = 0; i < plants.size() && i < previousInsecticide.size(); ++i) 
	{
		if (plants[i]) 
		{
			int currentInsecticide = plants[i]->getInsecticide();
			int diff = previousInsecticide[i] - currentInsecticide;
			plants[i]->addInsecticide(diff);
		}
	}
}

std::string Spray::getDescription() const 
{
	std::ostringstream oss;
	oss << "Sprayed insecticide on " << plants.size() << " plant(s)";
	if (!plants.empty() && plants[0]) 
	{
		oss << " [" << plants[0]->id();
		if (plants.size() > 1) 
		{
			oss << ", ...";
		}
		oss << "]";
	}
	return oss.str();
}
