#include "InventoryService.h"
#include <stdexcept>
#include <optional>
#include <iostream>

InventoryService::InventoryService(Inventory& store, Greenhouse& gh) : inv(store), gh(gh) {}

bool InventoryService::addPlant(std::string plantId, std::string speciesSku) 
{
	if (inv.byId.count(plantId)) return false;
  	Inventory::PlantRec rec{ plantId, speciesSku, Inventory::Status::Available };

  	inv.byId.emplace(plantId, rec);
  	inv.availBySku[speciesSku].insert(plantId);
  	return true;
}

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

int InventoryService::availableCount(std::string speciesSku)  
{
	auto it = inv.availBySku.find(speciesSku);
	return (it == inv.availBySku.end()) ? 0 : static_cast<int>(it->second.size());
}

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

int InventoryService::reservedCount(std::string speciesSku)  
{
	auto it = inv.reservedBySku.find(speciesSku);
	return (it == inv.reservedBySku.end()) ? 0 : static_cast<int>(it->second.size());
}

int InventoryService::soldCount(std::string speciesSku)  
{
	auto it = inv.soldBySku.find(speciesSku);
	return (it == inv.soldBySku.end()) ? 0 : static_cast<int>(it->second.size());
}

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


