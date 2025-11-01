
/**
 * @file InventoryService.h
 * @brief Inventory Service Observer implementation
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * The InventoryService class implements the NurseryObserver interface to manage
 * inventory updates in response to plant lifecycle events.
 */
#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H
#include <string>
#include <vector>
#include <optional>
#include "Inventory.h"
#include "NurseryObserver.h"
#include "Greenhouse.h"
#include "Events.h"

/**
 * @class InventoryService
 * @brief Concrete Observer implementation for inventory management
 * @details
 * Handles Plant events to update the inventory based on plant lifecycle changes.
 */
class InventoryService : public NurseryObserver
{

private:

	/**
	 * @brief Reference to the Inventory being managed
	 * @param inv The Inventory instance
	 * @param gh The Greenhouse instance
	 */
	Inventory& inv;
	Greenhouse& gh;

public:

	/**
	 * @brief Constructor for InventoryService
	 * @param store Reference to the Inventory to manage
	 * @param gn Reference to the Greenhouse instance
	 * @returns InventoryService instance
	 */
	explicit InventoryService(Inventory& store, Greenhouse& gn);

	/**
	 * @brief Adds a new plant to the inventory
	 * @param plantId The unique ID of the plant
	 * @param speciesSku The species SKU of the plant
	 * @returns true if the plant was added successfully, false otherwise
	 */
	bool addPlant(std::string plantId, std::string speciesSku);

	/**
	 * @brief Reserves a plant in the inventory
	 * @param plantId The unique ID of the plant
	 * @returns true if the plant was reserved successfully, false otherwise
	 */
	bool reservePlant(std::string plantId);

	/**
	 * @brief Effectively Sells a plant from the inventory
	 * @param plantId The unique ID of the plant
	 * @returns true if the plant was sold successfully, false otherwise
	 */
	bool markSold(std::string plantId);

	/**
	 * @brief Releases a plant from an order back to available inventory
	 * @param plantId The unique ID of the plant
	 * @returns void
	 */
	void releasePlantFromOrder(std::string plantId);

	/**
	 * @brief Finds the amount of available for purchase plants of a certain species
	 * @param speciesSku The species SKU to check
	 * @returns The count of available plants for the specified species
	 */
	int availableCount(std::string speciesSku);

	/**
	 * @brief Finds the amount of available plants of a certain species that are reserved
	 * @param speciesSku The species SKU to check
	 * @returns The count of reserved plants for the specified species
	 */
	int reservedCount(std::string speciesSku);

	/**
	 * @brief Finds the amount of sold plants of a certain species
	 * @param speciesSku The species SKU to check
	 * @returns The count of sold plants for the specified species
	 */
	int soldCount(std::string speciesSku);

	/**
	 * @brief Lists all available plants in the inventory
	 * @returns A vector of plant IDs that are available for purchase
	 */
	std::vector<std::string> listAvailablePlants();

    /**
	 * @brief Reaction to a Plant Event
	 * @param event The Plant event to react to
	 * @returns void
	 */
    void onEvent(events::Plant) override;
};

#endif // INVENTORYSERVICE_H