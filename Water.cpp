#include "Water.h"
#include "Plant.h"
#include <iostream>
#include <sstream>

Water::Water(const std::vector<Plant*>& p) : plants(p) {}

void Water::execute() 
{
	previousMoisture.clear();
	previousMoisture.reserve(plants.size());
	
	for (Plant* p : plants) 
	{
		if (p) 
		{
			previousMoisture.push_back(p->getMoisture());
			p->water();
		}
	}
}

void Water::undo() 
{
	for (size_t i = 0; i < plants.size() && i < previousMoisture.size(); ++i) 
	{
		if (plants[i]) 
		{
			int currentMoisture = plants[i]->getMoisture();
			int diff = previousMoisture[i] - currentMoisture;
			plants[i]->addWater(diff);
		}
	}
}

std::string Water::getDescription() const 
{
	std::ostringstream oss;
	oss << "Watered " << plants.size() << " plant(s)";
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

