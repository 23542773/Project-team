/**
 * @file Inventory.h
 * @brief Defines the Inventory structure used for tracking the status and location of all
 * matured, saleable plants within the system.
 */

#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <unordered_set>
#include <unordered_map>

/**
 * @struct Inventory
 * @brief A comprehensive structure containing records of all matured plants, tracking their status
 * through their sales lifecycle (Available, Reserved, Sold, etc.).
 */

struct Inventory
{
	/**
     * @enum Status
     * @brief Represents the current disposition or state of a plant for sales purposes.
     */

enum class Status {
        /** @brief The plant is ready and available for sale. */
        Available,
        /** @brief The plant has been allocated to an order but not yet sold. */
        Reserved,
        /** @brief The plant has been sold and removed from inventory. */
        Sold,
        /** @brief The plant is currently unhealthy or damaged and cannot be sold. */
        Wilted,
        /** @brief The plant is dead and should be disposed of. */
        Dead
    };

    /**
     * @struct PlantRec
     * @brief A record structure holding the key details for a single plant in the inventory.
     */
	struct PlantRec
    {
        /** @brief The unique identifier for the individual plant. */
        std::string plantId;
        /** @brief The Stock Keeping Unit (SKU) for the plant's species. */
        std::string speciesSku;
        /** @brief The current sales status of the plant. Defaults to Available. */
        Status status = Status::Available;
    };

	/**
     * @brief Main map storing all plant records, keyed by the unique plant ID.
     */
	std::unordered_map<std::string, PlantRec> byId;

	/**
     * @brief Index mapping species SKU to a set of plant IDs that are currently available for sale.
     */
	std::unordered_map<std::string, std::unordered_set<std::string>> availBySku;

	/**
     * @brief Index mapping species SKU to a set of plant IDs that are currently reserved for pending orders.
     */
  	std::unordered_map<std::string, std::unordered_set<std::string>> reservedBySku;

	/**
     * @brief Index mapping species SKU to a set of plant IDs that have been sold.
     */
  	std::unordered_map<std::string, std::unordered_set<std::string>> soldBySku;
};

#endif
