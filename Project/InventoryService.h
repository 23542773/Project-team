#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H
#include <string>
#include <vector>
#include <optional>
#include "Inventory.h"
#include "NurseryObserver.h"
#include "Greenhouse.h"
#include "Events.h"

class InventoryService : public NurseryObserver
{

private:

	Inventory& inv;
	Greenhouse& gh;

public:

	/// \brief Initializes to an Inventory
	explicit InventoryService(Inventory& store, Greenhouse& gn);

	/// \brief Adds a plant to the inventory
	bool addPlant(std::string plantId, std::string speciesSku);

	/// \brief Reserves a plant in the inventory
	bool reservePlant(std::string plantId);

	/// \brief Effectively Sells a plant from the inventory
	bool markSold(std::string plantId);

	/// \brief Releases a plant previously reserved from an order
	void releasePlantFromOrder(std::string plantId);

	/// \brief Finds the amount of available for purchase plants of a certain species
	int availableCount(std::string speciesSku);

	/// \brief Finds the amount of available plants of a certain speicies that are reserved
	int reservedCount(std::string speciesSku);

	/// \brief Finds the amount of sold plants of a certain species
	int soldCount(std::string speciesSku);

	/// \brief Returns a list of plantIds that are currently Available
	std::vector<std::string> listAvailablePlants();

    /// \brief Reaction to a Plant Event
    void onEvent(events::Plant) override;
};

#endif
