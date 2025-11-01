/**
 * @file InventoryService.cpp
 * @brief Implementation of InventoryService Observer methods
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * Implements the InventoryService class methods to handle inventory
 * updates in response to plant lifecycle events.
 */
#include "InventoryService.h"
#include <stdexcept>
#include <optional>
#include <iostream>

/**
 * @brief Constructor for InventoryService
 * @param store Reference to the Inventory to manage
 * @param gh Reference to the Greenhouse instance
 * @returns InventoryService instance
 */
InventoryService::InventoryService(Inventory& store, Greenhouse& gh) : inv(store), gh(gh) {}

/**
 * @brief Adds a new plant to the inventory
 * @param plantId The unique ID of the plant
 * @param speciesSku The species SKU of the plant
 * @returns true if the plant was added successfully, false otherwise
 */
bool InventoryService::addPlant(std::string plantId, std::string speciesSku) 
{
	if (inv.byId.count(plantId)) return false;
  	Inventory::PlantRec rec{ plantId, speciesSku, Inventory::Status::Available };

  	inv.byId.emplace(plantId, rec);
  	inv.availBySku[speciesSku].insert(plantId);
  	return true;
}

/**
 * @brief Releases a plant from an order back to available inventory
 * @param plantId The unique ID of the plant
 * @returns void
 */
void InventoryService::releasePlantFromOrder(std::string plantId) 
{
	auto it = inv.byId.find(plantId);
  	if (it == inv.byId.end()) return;

  	Inventory::PlantRec& rec = it->second;
  	if (rec.status != Inventory::Status::Reserved) return;

  	inv.reservedBySku[rec.speciesSku].erase(plantId);
  	rec.status = Inventory::Status::Available;
  	inv.availBySku[rec.speciesSku].insert(plantId);
}

/**
 * @brief Effectively Sells a plant from the inventory
 * @param plantId The unique ID of the plant
 * @returns true if the plant was sold successfully, false otherwise
 */
bool InventoryService::markSold(std::string plantId) 
{
  	auto it = inv.byId.find(plantId);
  	if (it == inv.byId.end()) return false;

  	Inventory::PlantRec& rec = it->second;
  	if (rec.status == Inventory::Status::Sold) return false;

  	if (rec.status == Inventory::Status::Available) 
  	{
    	inv.availBySku[rec.speciesSku].erase(plantId);
  	} 
  	else if (rec.status == Inventory::Status::Reserved)
  	{
    	inv.reservedBySku[rec.speciesSku].erase(plantId);
  	}
  	
  	rec.status = Inventory::Status::Sold;
  	inv.soldBySku[rec.speciesSku].insert(plantId);
  	
  	return true;
}

/**
 * @brief Finds the amount of available for purchase plants of a certain species
 * @param speciesSku The species SKU to check
 * @returns The count of available plants for the specified species
 */
int InventoryService::availableCount(std::string speciesSku)  
{
	auto it = inv.availBySku.find(speciesSku);
	return (it == inv.availBySku.end()) ? 0 : static_cast<int>(it->second.size());
}

/**
 * @brief Lists all available plants in the inventory
 * @returns A vector of plant IDs that are available for purchase
 */
std::vector<std::string> InventoryService::listAvailablePlants()
{
	std::vector<std::string> out;
	out.reserve(inv.availBySku.size());
	for (const auto& kv : inv.availBySku)
	{
		for (const auto& id : kv.second) out.push_back(id);
	}
	return out;
}

/**
 * @brief Finds the amount of available plants of a certain species that are reserved
 * @param speciesSku The species SKU to check
 * @returns The count of reserved plants for the specified species
 */
int InventoryService::reservedCount(std::string speciesSku)  
{
	auto it = inv.reservedBySku.find(speciesSku);
	return (it == inv.reservedBySku.end()) ? 0 : static_cast<int>(it->second.size());
}

/**
 * @brief Finds the amount of sold plants of a certain species
 * @param speciesSku The species SKU to check
 * @returns The count of sold plants for the specified species
 */
int InventoryService::soldCount(std::string speciesSku)  
{
	auto it = inv.soldBySku.find(speciesSku);
	return (it == inv.soldBySku.end()) ? 0 : static_cast<int>(it->second.size());
}

/**
 * @brief Reserves a plant in the inventory
 * @param plantId The unique ID of the plant
 * @returns true if the plant was reserved successfully, false otherwise
 */
bool InventoryService::reservePlant(std::string plantId)
{
    auto it = inv.byId.find(plantId);
    if (it == inv.byId.end()) return false;

    Inventory::PlantRec& rec = it->second;
    if (rec.status != Inventory::Status::Available) return false;

    rec.status = Inventory::Status::Reserved;

    auto skuIt = inv.availBySku.find(rec.speciesSku);

    if (skuIt != inv.availBySku.end()) skuIt->second.erase(plantId);

    inv.reservedBySku[rec.speciesSku].insert(plantId);
    return true;
}

/**
 * @brief Reaction to a Plant Event
 * @param event The Plant event to react to
 * @details
 * Handles plant lifecycle events to update inventory status.
 * @returns void
 */
void InventoryService::onEvent(events::Plant e)
{
    switch (e.type)
    {
        case events::PlantType::Matured:
        {
            auto it = inv.byId.find(e.plantId);
            if (it == inv.byId.end())
            {

                Inventory::PlantRec rec{ e.plantId, e.sku, Inventory::Status::Available };
                inv.byId.emplace(e.plantId, rec);
                inv.availBySku[e.sku].insert(e.plantId);
            }
            else
            {
                bool wasWilted = (it->second.status == Inventory::Status::Wilted);
                it->second.status = Inventory::Status::Available;
                inv.availBySku[e.sku].insert(e.plantId);
                inv.reservedBySku[e.sku].erase(e.plantId);
                inv.soldBySku[e.sku].erase(e.plantId);
            }
            
            break;
        }

        case events::PlantType::Wilted:
        {
            auto it = inv.byId.find(e.plantId);
            if (it != inv.byId.end())
            {
                if (it->second.status == Inventory::Status::Available)
                {
                    inv.availBySku[e.sku].erase(e.plantId);
                    it->second.status = Inventory::Status::Wilted;
                }
            }
            break;
        }

        case events::PlantType::Died:
        {
            inv.byId[e.plantId].status = Inventory::Status::Dead;
            inv.availBySku[e.sku].erase(e.plantId);
            inv.reservedBySku[e.sku].erase(e.plantId);
            inv.soldBySku[e.sku].erase(e.plantId);
            break;
        }
        default:
            break;
    }
}