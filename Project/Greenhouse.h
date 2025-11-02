/**
 * @file Greenhouse.h
 * @brief Defines the Greenhouse class, which manages all persistent Plant instances,
 * handles plant life cycle events, and acts as a subject for event notifications.
 */

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

// Forward declarations for external dependencies
class Iterator;
class PlantState;

/**
 * @class Greenhouse
 * @brief Manages the collection of all living Plant objects, tracking them by ID and SKU.
 *
 * This class is responsible for:
 * 1. Managing the lifecycle of plants (via `tickAll`).
 * 2. Handling new plant shipments.
 * 3. Acting as the **Subject** (`ServiceSubject`) to notify observers of Plant events (e.g., Matured).
 * 4. Providing **Iterator** factory methods for structured traversal of plants.
 */

class Greenhouse : public ServiceSubject 
{

public:

	/**
     * @brief Constructor for the Greenhouse.
     * @param p A pointer to the PlantRegistry used for prototyping/cloning when new plants are received.
     */

	Greenhouse(PlantRegistry* p);

  	/**
     * @brief Receives a batch of new plants for a given species SKU, generates unique IDs,
     * and adds them to the greenhouse collection.
     * @param speciesSku The SKU of the plant species being received.
     * @param batch The number of new plants to add.
     */

  	void receiveShipment(std::string speciesSku, int batch);

	/**
     * @brief Adds an already constructed Plant instance to the greenhouse's managed collection.
     * @param plant A unique pointer to the Plant object to be added.
     */

	void addPlant(std::unique_ptr<Plant> plant);

	/**
     * @brief Picks a colour from a predefined palette based on an index.
     * @param index The index (0-based) into the colour palette.
     * @return A string representing the selected colour (e.g., a hex code).
     */

	std::string pickColour(int index);

	/**
     * @brief Returns a pointer to a runtime Plant instance for a given plant ID.
     * @param plantId The unique identifier of the plant.
     * @return A raw pointer to the requested Plant instance, or nullptr if not present.
     */

	Plant* getPlant(const std::string& plantId);

	/**
     * @brief Counts how many plants of a particular species SKU currently exist in the greenhouse.
     * @param sku The species Stock Keeping Unit (SKU) to count.
     * @return The total number of plants matching the SKU.
     */

	int countBySku(const std::string& sku);

	/**
     * @brief Removes a plant from the greenhouse's managed collection (e.g., after being sold or dying).
     * @param plantId The unique identifier of the plant to remove.
     * @return true if the plant was successfully found and removed, false otherwise.
     */

	bool removePlant(const std::string& plantId);

	/**
     * @brief Advances the state/simulation time for all plants.
     *
     * This method iterates over all managed plants and calls an update/tick method on them,
     * potentially triggering state changes (e.g., from SeedlingState to GrowingState).
     */

	
	void tickAll();

	/**
     * @brief Factory method to create an Iterator that traverses all plants in the greenhouse.
     * @return A pointer to a newly created concrete Iterator object.
     */

	Iterator* createIterator() const;
	
	/**
     * @brief Factory method to create an Iterator that traverses only plants in a specific state.
     * @param state A pointer to the target PlantState object.
     * @return A pointer to a newly created concrete Iterator object.
     */

	Iterator* createStateIterator(const PlantState* state) const;
	
	/**
     * @brief Factory method to create an Iterator that traverses only plants of a specific SKU.
     * @param sku The Stock Keeping Unit (SKU) to filter the plants by.
     * @return A pointer to a newly created concrete Iterator object.
     */

	Iterator* createSkuIterator(const std::string& sku) const;

private:

	/**
     * @brief Maps a unique plant ID to its corresponding species SKU.
     */

	std::unordered_map<std::string, std::string> plantToSku;

	/**
     * @brief The main collection of live Plant instances, keyed by their unique plant ID.
     * Plants are managed using unique pointers.
     */

	std::unordered_map<std::string, std::unique_ptr<Plant>> plantInstances;

  	/**
     * @brief Simple counters used to generate sequence numbers for plant IDs per SKU.
     * E.g., ROSE-STD -> 3 means the next one will be #4.
     */

  	std::unordered_map<std::string, int> seqBySku;

  	/**
     * @brief Helper function to generate the next unique plant ID string based on the species SKU.
     * @param speciesSku The SKU to generate the ID prefix from.
     * @return The next unique ID (e.g., "ROSE-STD#4").
     */

  	std::string nextIdFor(std::string speciesSku);

	/**
     * @brief A pointer to the PlantRegistry, used as a prototype source for new plants.
     */

	PlantRegistry* proto;
};

#endif
