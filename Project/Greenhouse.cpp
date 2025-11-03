#include "Greenhouse.h"
#include <sstream>
#include <memory>
#include "WiltingState.h"
#include "Iterator.h"
#include "GreenhouseIterator.h"
#include "StateIterator.h"
#include "SkuIterator.h"


Greenhouse::Greenhouse(PlantRegistry* p) : proto(p) {}

void Greenhouse::receiveShipment(std::string speciesSku, int batch) 
{
    if (batch <= 0) return;

    for (int i = 0; i < batch; ++i) 
    {
      std::string colour = pickColour(i);
      std::string id = nextIdFor(speciesSku);  
      Plant* clone = proto->clone(speciesSku, id, colour);  
      if (clone) 
      {
          plantInstances.emplace(id, std::unique_ptr<Plant>(clone));
          plantToSku.emplace(id, speciesSku);
      }
    }

    events::Stock s{ speciesSku, events::StockType::Added };
    notify(s);
}

std::string Greenhouse::pickColour(int index) 
{
    static const std::vector<std::string> colours = {"Red","Yellow","Purple","Pink","White","Orange","Blue","Silver","Gold", "Green"};
    return colours[index % colours.size()];
}

Plant* Greenhouse::getPlant(const std::string& plantId)
{
  auto it = plantInstances.find(plantId);
  return (it == plantInstances.end()) ? nullptr : it->second.get();
}

void Greenhouse::addPlant(std::unique_ptr<Plant> plant)
{
    if (!plant) return;
    std::string id = plant->id();
    std::string sku = plant->sku(); 
    plantToSku[id] = sku;
    plantInstances[id] = std::move(plant);
}

int Greenhouse::countBySku(const std::string& sku)
{
    int count = 0;
    for (const auto& [id, skuStr] : plantToSku) 
    {
        if (skuStr == sku) ++count;
    }
    return count;
}

bool Greenhouse::removePlant(const std::string& plantId)
{
    auto it = plantInstances.find(plantId);
    if (it == plantInstances.end()) return false;
  
    plantInstances.erase(it);
    plantToSku.erase(plantId);
  
    return true;
}

std::string Greenhouse::nextIdFor(std::string speciesSku) 
{
    int& n = seqBySku[speciesSku];
    std::ostringstream os;
    os << speciesSku << "#" << (++n);
    return os.str();
}
 
void Greenhouse::tickAll() 
{
    std::vector<std::string> toRemove;

    Iterator* it = createIterator();
    for (it->first(); !it->isDone(); it->next())
    { 
        Plant* plant = it->currentItem();
        if (!plant) continue;
        
        PlantState* before = plant->getPlantState();  
        std::string beforeName = before->name();
    
        plant->getPlantState()->checkChange(*plant);
        
        PlantState* after = plant->getPlantState();
        std::string afterName = after->name();
        
        if (before != after) 
        {  
            if (after == &MatureState::getInstance()) 
            {
                events::Plant e{ plant->id(), plant->sku(), events::PlantType::Matured };
                notify(e);
            }

            else if (after == &WiltingState::getInstance())
            {
                events::Plant e{ plant->id(), plant->sku(), events::PlantType::Wilted };
                notify(e);
            }
        }
        if(after == &DeadState::getInstance())
        {
            events::Plant e{ plant->id(), plant->sku(), events::PlantType::Died };
            notify(e);
            toRemove.push_back(plant->id());
        }
    }
    delete it;

    for (const auto& deadId : toRemove) 
    {
        removePlant(deadId);
    }
}

Iterator* Greenhouse::createIterator() const 
{
    std::vector<Plant*> snapshot;
    snapshot.reserve(plantInstances.size());
    for (auto& kv : const_cast<Greenhouse*>(this)->plantInstances) 
    {
        snapshot.push_back(kv.second.get());
    }
    return new GreenhouseIterator(snapshot);
}

Iterator* Greenhouse::createStateIterator(const PlantState* state) const 
{
    std::vector<Plant*> snapshot;
    snapshot.reserve(plantInstances.size());
    for (auto& kv : const_cast<Greenhouse*>(this)->plantInstances) 
    {
        snapshot.push_back(kv.second.get());
    }
    return new StateIterator(snapshot, state);
}

Iterator* Greenhouse::createSkuIterator(const std::string& sku) const 
{
    std::vector<Plant*> snapshot;
    snapshot.reserve(plantInstances.size());
    for (auto& kv : const_cast<Greenhouse*>(this)->plantInstances) 
    {
        snapshot.push_back(kv.second.get());
    }
    return new SkuIterator(snapshot, sku);
}
