/**
 * @file Restock.h
 * @brief Defines the Restock command, a concrete implementation of the Command pattern
 * for adding new plants to the Greenhouse.
 */
#ifndef RESTOCK_H
#define RESTOCK_H

#include "Command.h"
#include <string>
#include <vector>

class Greenhouse;

/**
 * @class Restock
 * @brief A concrete Command that encapsulates the request to receive a shipment (restock)
 * of new plants into the Greenhouse.
 *
 * This command supports undo functionality by tracking the unique IDs of the plants
 * that were added during execution.
 */

class Restock : public Command 
{

private:
/**
 * @brief A reference to the Greenhouse instance, which is the receiver of this command.
 */

	Greenhouse& greenhouse;

	/**
     * @brief The Stock Keeping Unit (SKU) of the species to be restocked.
     */

	std::string speciesSku;
	/**
     * @brief The number of plants to be added in this restock operation.
     */
	int batchSize;

	/**
     * @brief Stores the unique IDs of the plants that were successfully added to the
     * Greenhouse during the `execute()` call. This is essential for undo.
     */

	std::vector<std::string> addedPlantIds;

public:
/**
 * @brief Constructor for the Restock command.
 * @param gh A reference to the Greenhouse object that will process the restock.
 * @param sku The SKU of the species being restocked.
 * @param batch The number of plants in the shipment batch.
 */

	Restock(Greenhouse& gh, const std::string& sku, int batch);
	/**
     * @brief Executes the restock command by calling the appropriate method on the Greenhouse.
     * The IDs of the newly added plants are stored in `addedPlantIds`.
     */

	void execute() override;

	/**
     * @brief Undoes the restock command.
     *
     * This iterates through `addedPlantIds` and removes each corresponding plant from the Greenhouse.
     */

	void undo() override;

	/**
     * @brief Provides a descriptive string for the command.
     * @return A string describing the restock action (e.g., "Restock 10 units of ROSE-STD").
     */
	
	std::string getDescription() const override;
};

#endif
