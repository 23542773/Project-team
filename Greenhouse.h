#ifndef GREENHOUSE_H
#define GREENHOUSE_H
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include "ServiceSubject.h"   
#include "Events.h"    
#include "PlantRegistry.h"    
#include "MatureState.h"
#include "DeadState.h"
#include "WiltingState.h"
#include "SeedlingState.h"
#include "GrowingState.h"
#include "Plant.h"
#include <memory>
#include "SpeciesCatalog.h"

class Iterator;
class PlantState;

/// \brief Minimal Greenhouse used by NurseryHub to map Plant IDs to SKUs, accept shipments, and emit Plant events (e.g. Matured).
class Greenhouse : public ServiceSubject 
{

public:

	Greenhouse(PlantRegistry* p);

  	/// \brief Receive 'batch' new plants for the given species SKU.
  	void receiveShipment(std::string speciesSku, int batch);

	void addPlant(std::unique_ptr<Plant> plant);

	/// \brief Pick a colour from the greenhouse palette based on an index.

	std::string pickColour(int index);

	/// \brief Return pointer to a runtime Plant instance for a given plantId, or nullptr if not present.
	Plant* getPlant(const std::string& plantId);

	/// \brief Count how many plants of a particular species SKU exist in the greenhouse.
	int countBySku(const std::string& sku);

	/// \brief Remove a plant from the greenhouse (e.g., when sold).
	bool removePlant(const std::string& plantId);

	
	void tickAll();

	/// \brief Create an iterator for all plants
	Iterator* createIterator() const;
	
	/// \brief Create an iterator for plants in a specific state
	Iterator* createStateIterator(const PlantState* state) const;
	
	/// \brief Create an iterator for plants of a specific SKU
	Iterator* createSkuIterator(const std::string& sku) const;

private:

	std::unordered_map<std::string, std::string> plantToSku;

	std::unordered_map<std::string, std::unique_ptr<Plant>> plantInstances;

  	// simple counters to generate plant IDs per SKU
  	std::unordered_map<std::string, int> seqBySku;

  	// helper to make a unique id, e.g. "ROSE-STD#3"
  	std::string nextIdFor(std::string speciesSku);

	PlantRegistry* proto;
};

#endif
