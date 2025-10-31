#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <unordered_set>
#include <unordered_map>

/// \brief Inventory struct containing records of all Matured plants and their status along its sale lifetime.
struct Inventory
{
	/// \brief Status that the plant is in
	enum class Status { Available, Reserved, Sold, Wilted, Dead };

	/// \brief Plant Record holding a plantId, speciesSku and status of the plant.
	struct PlantRec
	{
		std::string plantId;
		std::string speciesSku;
		Status status = Status::Available;
	};

	/// \brief Map of plantId <-> PlantRecord.
	std::unordered_map<std::string, PlantRec> byId;

	/// \brief Map of speciesSku <-> plantId of all plants available.
	std::unordered_map<std::string, std::unordered_set<std::string>> availBySku;

	/// \brief Map of speciesSku <-> plantId of all plants reserved.
  	std::unordered_map<std::string, std::unordered_set<std::string>> reservedBySku;

	/// \brief Map of speciesSku <-> plantId of all plants sold.
  	std::unordered_map<std::string, std::unordered_set<std::string>> soldBySku;
};

#endif
