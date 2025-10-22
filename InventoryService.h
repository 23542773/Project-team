#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H
#include <string>
#include "Inventory.h"
#include "ServiceSubject.h"

class InventoryService : public ServiceSubject, public ServiceColleague
{

private:

	/// \brief Reference to inventory
	Inventory& inv;

	/// \brief Function to move a plant from one map to another based on its status
	void move(std::string plantId, Inventory::Status from, Inventory::Status to);

	/// \brief Function to restock a specific species if below the threshold
	void emitLowIfNeeded(std::string speciesSku);

public:

	/// \brief Initializes to an Inventory
	explicit InventoryService(Inventory& store);

	/// \brief Adds a plant to the inventory
	bool addPlant(std::string plantId, std::string speciesSku);

	/// \brief Reserves a plant in the inventory
	bool reservePlant(std::string plantId);

	/// \brief Releases a plant in the inventory (Wilted State)
	void releasePlant(std::string plantId);

	/// \brief Effectively Sells a plant from the inventory
	bool markSold(std::string plantId);

	/// \brief Attempts to reserve any plants available of a certain species
	std::optional<std::string> reserveAnyAvailable(std::string speciesSku);

	/// \brief Reserves Batch of plants based on Ids
	std::vector<std::string> reserveBatch(std::vector<std::string>& plantIds);

	/// \brief Finds the amount of available for purchase plants of a certain species
	int availableCount(std::string speciesSku);

	/// \brief Finds the amount of available plants of a certain speicies that are reserved
	int reservedCount(std::string speciesSku);

	/// \brief Finds the amount of sold plants of a certain species
	int soldCount(std::string speciesSku);

	/// \brief Used to set the threshold for when a particular species must request a restock
	void setLowThreshold(std::string speciesSku, int threshold);
};

#endif
