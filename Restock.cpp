#include "Restock.h"
#include "Greenhouse.h"
#include "Iterator.h"
#include <iostream>
#include <sstream>
#include <unordered_set>

Restock::Restock(Greenhouse& gh, const std::string& sku, int batch) : greenhouse(gh), speciesSku(sku), batchSize(batch) {}

void Restock::execute() 
{
	addedPlantIds.clear();
	std::unordered_set<std::string> beforeIds;
	Iterator* it = greenhouse.createSkuIterator(speciesSku);

	for (it->first(); !it->isDone(); it->next()) 
	{
		Plant* p = it->currentItem();
		if (p) beforeIds.insert(p->id());
	}
	delete it;
	greenhouse.receiveShipment(speciesSku, batchSize);

	it = greenhouse.createSkuIterator(speciesSku);
	for (it->first(); !it->isDone(); it->next()) 
	{
		Plant* p = it->currentItem();

		if (p && beforeIds.find(p->id()) == beforeIds.end()) 
		{
			addedPlantIds.push_back(p->id());
		}
	}
	delete it;
}

void Restock::undo() 
{
	if (addedPlantIds.empty()) 
	{
		std::cerr << "No plants to remove for undo.\n";
		return;
	}
	
	for (const auto& id : addedPlantIds)
	 {
		greenhouse.removePlant(id);
	}
	addedPlantIds.clear();
}

std::string Restock::getDescription() const 
{
	std::ostringstream oss;
	oss << "Restocked " << batchSize << " x " << speciesSku;
	return oss.str();
}
