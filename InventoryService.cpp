#include "InventoryService.h"
#include <stdexcept>
#include <optional>

InventoryService::InventoryService(Inventory& store) : inv(store) {}

void InventoryService::move(std::string plantId, Inventory::Status from, Inventory::Status to) 
{
	auto it = inv.byId.find(plantId);
  	if (it == inv.byId.end()) throw std::runtime_error("Unknown plantId: " + plantId);

  	Inventory::PlantRec& rec = it->second;
  	if (rec.status != from) throw std::runtime_error("Illegal status transition for " + plantId);

  	std::string& sku = rec.speciesSku;

  	switch (from) 
  	{
    	case Inventory::Status::Available: inv.availBySku[sku].erase(plantId); break;
    	case Inventory::Status::Reserved: inv.reservedBySku[sku].erase(plantId); break;
    	case Inventory::Status::Sold: inv.soldBySku[sku].erase(plantId); break;
  	}
	switch (to) 
  	{
    	case Inventory::Status::Available: inv.availBySku[sku].insert(plantId); break;
    	case Inventory::Status::Reserved: inv.reservedBySku[sku].insert(plantId); break;
   		case Inventory::Status::Sold: inv.soldBySku[sku].insert(plantId); break;
  	}
  	rec.status = to;
}

void InventoryService::emitLowIfNeeded(std::string speciesSku) 
{
	auto thrIt = inv.lowThresholdBySku.find(speciesSku);
  	if (thrIt == inv.lowThresholdBySku.end()) return;

  	int threshold = thrIt->second;
  	int avail = availableCount(speciesSku);

  	if (avail <= threshold) 
  	{
    	notify(events::Stock{ speciesSku, StockType::Low });
  	}
}

bool InventoryService::addPlant(std::string plantId, std::string speciesSku) 
{
	if (inv.byId.count(plantId)) return false;
  	Inventory::PlantRec rec{ plantId, speciesSku, Inventory::Status::Available };

  	inv.byId.emplace(plantId, rec);
  	inv.availBySku[speciesSku].insert(plantId);
  	return true;
}

bool InventoryService::reservePlant(std::string plantId) 
{
	auto it = inv.byId.find(plantId);
  	if (it == inv.byId.end()) return false;

  	Inventory::PlantRec& rec = it->second;
  	if (rec.status != Inventory::Status::Available) return false;

  	move(plantId, Inventory::Status::Available, Inventory::Status::Reserved);
  	notify(events::Stock{ rec.plantId, StockType::Reserved });

  	emitLowIfNeeded(rec.speciesSku);
  	return true;
}

void InventoryService::releasePlant(std::string plantId) 
{
	auto it = inv.byId.find(plantId);
  	if (it == inv.byId.end()) return;

  	Inventory::PlantRec& rec = it->second;
  	if (rec.status != Inventory::Status::Reserved) return;

  	move(plantId, Inventory::Status::Reserved, Inventory::Status::Available);
  	notify(events::Stock{ rec.plantId, StockType::Released });
}

bool InventoryService::markSold(std::string plantId) 
{
  	auto it = inv.byId.find(plantId);
  	if (it == inv.byId.end()) return false;

  	Inventory::PlantRec& rec = it->second;
  	if (rec.status == Inventory::Status::Sold) return false;

  	if (rec.status == Inventory::Status::Available) 
  	{
    	move(plantId, Inventory::Status::Available, Inventory::Status::Sold);
  	} 
  	else 
  	{
    	move(plantId, Inventory::Status::Reserved, Inventory::Status::Sold);
  	}

  	notify(events::Stock{ rec.plantId, StockType::Sold });
  	emitLowIfNeeded(rec.speciesSku);
  	return true;
}

std::optional<std::string> InventoryService::reserveAnyAvailable(std::string speciesSku) 
{
	std::unordered_set<std::string>& setRef = inv.availBySku[speciesSku];
	if (setRef.empty()) return std::nullopt;

	const std::string& chosen = *setRef.begin();
	if (reservePlant(chosen)) return chosen;
	return std::nullopt;
}

std::vector<std::string> InventoryService::reserveBatch(std::vector<std::string>& plantIds) 
{
	std::vector<std::string> reserved;
	reserved.reserve(plantIds.size());
	
	for (std::string& id : plantIds) 
  	{
    	if (reservePlant(id)) reserved.push_back(id);
  	}
  	return reserved;
}

int InventoryService::availableCount(std::string speciesSku)  
{
	auto it = inv.availBySku.find(speciesSku);
	return (it == inv.availBySku.end()) ? 0 : static_cast<int>(it->second.size());
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

void InventoryService::setLowThreshold(std::string speciesSku, int threshold) 
{
	inv.lowThresholdBySku[speciesSku] = threshold;
	emitLowIfNeeded(speciesSku);
}