#include "Fertilize.h"
#include "Plant.h"
#include <iostream>
#include <sstream>

Fertilize::Fertilize(const std::vector<Plant*>& p) : plants(p) {}

void Fertilize::execute() 
{

	previousHealth.clear();
	previousHealth.reserve(plants.size());
	
	for (Plant* p : plants) 
	{
		if (p) 
		{
			previousHealth.push_back(p->getHealth());
			p->fertilize();
		}
	}
}

void Fertilize::undo() 
{
	for (size_t i = 0; i < plants.size() && i < previousHealth.size(); ++i) 
	{
		if (plants[i]) 
		{
			int currentHealth = plants[i]->getHealth();
			int diff = previousHealth[i] - currentHealth;
			plants[i]->addHealth(diff);
		}
	}
}

std::string Fertilize::getDescription() const 
{
	std::ostringstream oss;
	oss << "Fertilized " << plants.size() << " plant(s)";
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
