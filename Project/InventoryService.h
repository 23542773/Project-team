/**
 * @file InventoryService.h
 * @brief Defines the InventoryService class, which manages plant inventory and acts
 * as an Observer for Nursery events.
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
 * @brief Manages the status, reservation, and sales of matured plants stored in the Inventory structure.
 *
 * This class is a concrete **NurseryObserver** that listens for plant status changes
 * (e.g., Matured, Wilted) and updates the sales inventory accordingly. It provides
 * all core business logic for stock management.
 */

class InventoryService : public NurseryObserver
{

private:
	/**
     * @brief A reference to the main Inventory data structure.
     */

	Inventory& inv;

	/**
     * @brief A reference to the Greenhouse, which holds the live plant instances.
     */

	Greenhouse& gh;

public:

	/**
     * @brief Initializes the InventoryService with references to the Inventory data
     * and the Greenhouse instance.
     * @param store A reference to the Inventory data structure to manage.
     * @param gn A reference to the Greenhouse instance.
     */

	explicit InventoryService(Inventory& store, Greenhouse& gn);

	/**
     * @brief Adds a newly matured plant to the available inventory.
     * @param plantId The unique ID of the plant.
     * @param speciesSku The SKU of the plant's species.
     * @return true if the plant was successfully added, false otherwise (e.g., if ID already exists).
     */

	bool addPlant(std::string plantId, std::string speciesSku);

	/**
     * @brief Changes a plant's status from Available to Reserved.
     * @param plantId The unique ID of the plant to reserve.
     * @return true if the plant was successfully reserved, false if it wasn't available.
     */

	bool reservePlant(std::string plantId);

	/**
     * @brief Changes a plant's status from Reserved to Sold, and potentially removes it from the Greenhouse.
     * @param plantId The unique ID of the plant to mark as sold.
     * @return true if the plant was successfully marked sold, false otherwise.
     */

	bool markSold(std::string plantId);

	/**
     * @brief Reverts a plant's status from Reserved back to Available.
     * @param plantId The unique ID of the plant to release.
     */

	void releasePlantFromOrder(std::string plantId);

	/**
     * @brief Finds the total amount of plants of a certain species that are currently **Available**.
     * @param speciesSku The SKU to check the count for.
     * @return The count of available plants.
     */

	int availableCount(std::string speciesSku);

	/**
     * @brief Finds the total amount of plants of a certain species that are currently **Reserved**.
     * @param speciesSku The SKU to check the count for.
     * @return The count of reserved plants.
     */

	int reservedCount(std::string speciesSku);

	/**
     * @brief Finds the total amount of plants of a certain species that have been **Sold**.
     * @param speciesSku The SKU to check the count for.
     * @return The count of sold plants.
     */
	int soldCount(std::string speciesSku);

	/**
     * @brief Returns a list of the unique IDs of all plants currently marked as Available.
     * @return A vector of strings containing plant IDs.
     */
	std::vector<std::string> listAvailablePlants();

    /**
     * @brief The concrete implementation of the Observer update method.
     *
     * This method reacts to plant lifecycle events (e.g., Matured, Wilted, Died)
     * and updates the inventory records accordingly.
     *
     * @param event The Plant event data structure.
     */
    void onEvent(events::Plant) override;
};

#endif
