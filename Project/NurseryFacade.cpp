#include "NurseryFacade.h"
#include "InventoryService.h"
#include "SalesService.h"
#include "StaffService.h"
#include "CustomerService.h"
#include "Greenhouse.h"
#include "SpeciesCatalog.h"
#include "PlantRegistry.h"
#include "Water.h"
#include "Fertilize.h"
#include "Spray.h"
#include "Restock.h"
#include "MacroCommand.h"
#include "SpeciesFlyweight.h"
#include "PlantFlyweight.h"
#include "Plant.h"
#include "Events.h"
#include "random"
#include "Iterator.h"
#include "WiltingState.h"
 
// Constructor
NurseryFacade::NurseryFacade(InventoryService* inv, SalesService* sales, StaffService* staff, 
    CustomerService* customers, Greenhouse* greenhouse, SpeciesCatalog* catalog, ActionLog* invoker)
    : inv(inv), sales(sales), staff(staff), customerService(customers), greenhouse(greenhouse), catalog(catalog), invoker(invoker) {}


std::vector<Plant*> NurseryFacade::browseAvailable()
{
    std::vector<Plant*> out;
    if (!inv || !greenhouse) return out;

    std::vector<std::string> ids = inv->listAvailablePlants();
    out.reserve(ids.size());

    for (const auto& id : ids)
    {
        Plant* p = greenhouse->getPlant(id);
        if (p) out.push_back(p);
    }

    return out;
}

Receipt NurseryFacade::checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid)
{
    Receipt receipt;
    receipt.success = false;
    receipt.message = "Service unavailable";
    
    if (!sales || !inv || !staff || !customerService) 
    {
        return receipt;
    }
    
    if (!customerService->getCustomer(customerId)) 
    {
        receipt.message = "Invalid customer";
        return receipt;
    }
    
    if (lines.empty())
    {
        receipt.message = "Cart is empty";
        return receipt;
    }
    
    double total = 0.0;
    for (const auto& line : lines) 
    {
        total += line.finalCost;
    }
    
    receipt.totalCost = total;
    receipt.amountPaid = amountPaid;
    
    if (amountPaid < total) 
    {
        receipt.message = "Insufficient payment. Required: R" + std::to_string(total);
        receipt.change = 0.0;
        return receipt;
    }
    
    std::vector<events::OrderLine> finalized;
    for (const auto& line : lines) 
    {
        bool ok = inv->reservePlant(line.plantId);
        if (ok) finalized.push_back(line);
    }
    
    if (finalized.empty()) 
    {
        receipt.message = "No items available";
        return receipt;
    }
    
    receipt = sales->checkout(customerId, finalized, amountPaid);
    
    if (receipt.success) 
    {
        std::string staffId = staff->leastLoaded();
        if (!staffId.empty()) 
        {
            staff->assignOrder(staffId, receipt.orderId);
            sales->assign(receipt.orderId, staffId);
            customerService->assignOrderToCustomer(receipt.orderId, customerId);
        }
    } 
    
    else 
    {
        for (const auto& line : finalized) 
        {
            inv->releasePlantFromOrder(line.plantId);
        }
    }
    return receipt;
}


std::vector<Receipt> NurseryFacade::getCustomerReceipts(std::string customerId)
{
    if (!sales) return {};
    return sales->getCustomerReceipts(customerId);
}


Plant* NurseryFacade::getPlant(std::string id) 
{
    if (!greenhouse) return nullptr;
    return greenhouse->getPlant(id);
}

std::vector<events::Order> NurseryFacade::getCustomerOrders(std::string customerId) 
{
    if (!sales) return {};
    return sales->getOrdersByCustomer(customerId);
}

std::vector<events::Order> NurseryFacade::getStaffOrders(std::string staffId) 
{
    if (!sales) return {};
    return sales->getOrdersByStaff(staffId);
}

std::vector<Staff> NurseryFacade::listAllStaff()
{
    if (!staff) return {};
    return staff->listStaff();
}

std::vector<Customer> NurseryFacade::listAllCustomers()
{
    if (!customerService) return {};
    return customerService->getAllCustomers();
}

std::vector<std::shared_ptr<PlantFlyweight>> NurseryFacade::listAllSpecies() 
{
    return catalog ? catalog->getAll() : std::vector<std::shared_ptr<PlantFlyweight>>{};
}

// restockSpecies removed — use enqueueRestock and process methods to go through the command system

int NurseryFacade::getSpeciesQuantity(std::string sku)
{
    if (!greenhouse) return 0;
    return greenhouse->countBySku(sku);
}

std::vector<Plant*> NurseryFacade::listAllPlants()
{
    std::vector<Plant*> result;
    if (!greenhouse) return result;
    Iterator* it = greenhouse->createIterator();
    if (it) 
    {
        for (it->first(); !it->isDone(); it->next()) 
        {
            Plant* p = it->currentItem();
            if (p) result.push_back(p);
        }
        delete it;
    }
    return result;
}

void NurseryFacade::waterPlants(std::vector<Plant*>& plants)
{
    if (plants.empty()) return;

    if (invoker) 
    {
        auto cmd = std::make_unique<Water>(plants);
        cmd->setUserId("STAFF");
        cmd->setAction("WATER");
        cmd->setUndoable(false);
        invoker->enqueue(std::move(cmd));
        invoker->processNext();
    }
}

void NurseryFacade::fertilizePlants(std::vector<Plant*>& plants)
{
    if (plants.empty()) return;

    if (invoker) 
    {
        auto cmd = std::make_unique<Fertilize>(plants);
        cmd->setUserId("STAFF");
        cmd->setAction("FERTILIZE");
        cmd->setUndoable(false);
        invoker->enqueue(std::move(cmd));
        invoker->processNext();
    } 
}

void NurseryFacade::sprayInsecticide(std::vector<Plant*>& plants)
{
    if (plants.empty()) return;

    if (invoker) 
    {
        auto cmd = std::make_unique<Spray>(plants);
        cmd->setUserId("STAFF");
        cmd->setAction("SPRAY");
        cmd->setUndoable(false);
        invoker->enqueue(std::move(cmd));
        invoker->processNext();
    } 
}

void NurseryFacade::tickAllPlants() 
{
    if (greenhouse) greenhouse->tickAll();
}

void NurseryFacade::runMorningRoutine(std::vector<Plant*>& plants)
{
    if (plants.empty()) return;

    if (invoker) 
    {
        auto macro = std::make_unique<MacroCommand>("MORNING ROUTINE");
        macro->setUserId("STAFF");
        macro->setAction("MORNING");
        macro->setUndoable(false);

        macro->addCommand(std::make_unique<Water>(plants));
        macro->addCommand(std::make_unique<Fertilize>(plants));

        invoker->enqueue(std::move(macro));
        invoker->processNext();
        return;
    }
}

void NurseryFacade::runNightRoutine(std::vector<Plant*>& plants)
{
    if (plants.empty()) return;

    if (invoker) 
    {
        auto macro = std::make_unique<MacroCommand>("NIGHT ROUTINE");
        macro->setUserId("STAFF");
        macro->setAction("NIGHT");
        macro->setUndoable(false);

        macro->addCommand(std::make_unique<Water>(plants));
        macro->addCommand(std::make_unique<Spray>(plants));

        invoker->enqueue(std::move(macro));
        invoker->processNext();
        return;
    }
}

void NurseryFacade::runUrgentCare()
{
    if (!greenhouse || !invoker) return;

    Iterator* it = greenhouse->createStateIterator(&WiltingState::getInstance());
    if (!it) return;

    std::vector<Plant*> wiltingPlants;
    for (it->first(); !it->isDone(); it->next()) 
    {
        Plant* p = it->currentItem();
        if (p) wiltingPlants.push_back(p);
    }
    delete it;

    if (wiltingPlants.empty()) 
    {
        return;
    }

    auto macro = std::make_unique<MacroCommand>("URGENT CARE");
    macro->setUserId("STAFF");
    macro->setAction("URGENT");
    macro->setUndoable(false);

    macro->addCommand(std::make_unique<Fertilize>(wiltingPlants));
    macro->addCommand(std::make_unique<Fertilize>(wiltingPlants));
    macro->addCommand(std::make_unique<Fertilize>(wiltingPlants));
    macro->addCommand(std::make_unique<Water>(wiltingPlants));
    macro->addCommand(std::make_unique<Spray>(wiltingPlants));

    invoker->enqueue(std::move(macro));
    invoker->processNext();
}

bool NurseryFacade::isValidCustomer(std::string id)
{
    return (customerService && customerService->getCustomer(id));
}

bool NurseryFacade::isValidStaff(std::string id)
{
    return (staff && staff->getStaff(id));
}

bool NurseryFacade::completeOrder(std::string orderId)
{
    if (!sales || !staff || !inv || !greenhouse) return false;
    
    auto orderOpt = sales->get(orderId);
    if (!orderOpt) return false;
    
    events::Order order = *orderOpt;
    if (order.status == events::OrderStatus::Completed) 
    {
        return false;
    }
    
    for (const auto& line : order.lines) 
    {
        inv->markSold(line.plantId);
        greenhouse->removePlant(line.plantId);
    }
    
    staff->completeOrder(orderId);
    
    bool updated = sales->updateStatus(orderId, events::OrderStatus::Completed);
    if (!updated) return false;
    return true;
}


std::vector<Message> NurseryFacade::getConversation(const std::string& userA, const std::string& userB)
{
    Staff* staffA = staff ? staff->getStaff(userA) : nullptr;
    if (staffA) 
    {
        return staffA->getConversation(userB);
    }
    
    Customer* custA = customerService ? customerService->getCustomer(userA) : nullptr;
    if (custA) 
    {
        return custA->getConversation(userB);
    }
    return {};
}

Customer* NurseryFacade::getCustomer(std::string id)
{
    if (!customerService) return nullptr;
    return customerService->getCustomer(id);
}

Staff* NurseryFacade::getStaff(std::string id)
{
    if (!staff) return nullptr;
    return staff->getStaff(id);
}

std::vector<Plant*> NurseryFacade::getPersonalizedRecommendations(const std::string& customerId)
{
    if (!customerService || !sales || !greenhouse) return {};
    
    std::vector<events::Order> orders = getCustomerOrders(customerId);
    
    if (orders.empty()) 
    {
        auto allPlants = browseAvailable();
        Season currentSeason = Plant::currentSeason();
        
        std::vector<Plant*> seasonalPlants;
        std::vector<Plant*> otherPlants;
        
        for (auto* p : allPlants) 
        {
            auto* fly = dynamic_cast<SpeciesFlyweight*>(p->getSpeciesFly());
            if (fly && fly->getThrivingSeason() == currentSeason) 
            {
                seasonalPlants.push_back(p);
            } 
            else 
            {
                otherPlants.push_back(p);
            }
        }
        
        std::vector<Plant*> result;
        
        result.insert(result.end(), seasonalPlants.begin(), seasonalPlants.end());
        
        if (result.size() < 15 && !otherPlants.empty()) 
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(otherPlants.begin(), otherPlants.end(), g);
            
            int toAdd = std::min(15 - static_cast<int>(result.size()), static_cast<int>(otherPlants.size()));
            result.insert(result.end(), otherPlants.begin(), otherPlants.begin() + toAdd);
        }
        
        return result;
    }
    
    std::unordered_set<std::string> purchasedPlantIds;
    for (const auto& order : orders) 
    {
        for (const auto& line : order.lines) 
        {
            purchasedPlantIds.insert(line.plantId);
        }
    }
    
    if (purchasedPlantIds.empty()) 
    {
        auto allPlants = browseAvailable();
        Season currentSeason = Plant::currentSeason();
        
        std::vector<Plant*> seasonalPlants;
        std::vector<Plant*> otherPlants;
        
        for (auto* p : allPlants) 
        {
            auto* fly = dynamic_cast<SpeciesFlyweight*>(p->getSpeciesFly());
            if (fly && fly->getThrivingSeason() == currentSeason) 
            {
                seasonalPlants.push_back(p);
            } 

            else 
            {
                otherPlants.push_back(p);
            }
        }
        
        std::vector<Plant*> result;
        result.insert(result.end(), seasonalPlants.begin(), seasonalPlants.end());
        
        if (result.size() < 15 && !otherPlants.empty()) 
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(otherPlants.begin(), otherPlants.end(), g);
            
            int toAdd = std::min(15 - static_cast<int>(result.size()), static_cast<int>(otherPlants.size()));
            result.insert(result.end(), otherPlants.begin(), otherPlants.begin() + toAdd);
        }
        
        return result;
    }
    
    std::unordered_map<std::string, int> biomeCount; 
    std::vector<Plant*> purchasedPlants;
    
    for (const auto& plantId : purchasedPlantIds) 
    {
        Plant* p = greenhouse->getPlant(plantId);
        if (p) 
        {
            purchasedPlants.push_back(p);
            std::string biome = p->biome();
            biomeCount[biome]++;
        }
    }
    
    if (purchasedPlants.empty()) 
    {
        auto allPlants = browseAvailable();
        Season currentSeason = Plant::currentSeason();
        
        std::vector<Plant*> seasonalPlants;
        std::vector<Plant*> otherPlants;
        
        for (auto* p : allPlants) 
        {
            auto* fly = dynamic_cast<SpeciesFlyweight*>(p->getSpeciesFly());
            if (fly && fly->getThrivingSeason() == currentSeason) 
            {
                seasonalPlants.push_back(p);
            } 

            else 
            {
                otherPlants.push_back(p);
            }
        }
        
        std::vector<Plant*> result;
        result.insert(result.end(), seasonalPlants.begin(), seasonalPlants.end());
        
        if (result.size() < 15 && !otherPlants.empty()) 
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(otherPlants.begin(), otherPlants.end(), g);
            
            int toAdd = std::min(15 - static_cast<int>(result.size()), static_cast<int>(otherPlants.size()));
            result.insert(result.end(), otherPlants.begin(), otherPlants.begin() + toAdd);
        }
        
        return result;
    }
    
    std::string favoriteBiome;
    int maxCount = 0;
    for (const auto& [biome, count] : biomeCount) 
    {
        if (count > maxCount) 
        {
            maxCount = count;
            favoriteBiome = biome;
        }
    }
    
    auto available = browseAvailable();
    Season currentSeason = Plant::currentSeason();
    
    std::vector<Plant*> favoriteBiomePlants;
    std::vector<Plant*> seasonalPlants;
    std::vector<std::pair<Plant*, double>> careSimilarPlants; 
    std::vector<Plant*> otherPlants;
    
    for (auto* candidate : available)
     {
        if (purchasedPlantIds.count(candidate->id())) continue;
        
        auto* candidateFly = dynamic_cast<SpeciesFlyweight*>(candidate->getSpeciesFly());
        if (!candidateFly) continue;
        
        if (candidate->biome() == favoriteBiome) 
        {
            favoriteBiomePlants.push_back(candidate);
        } 

        else if (candidateFly->getThrivingSeason() == currentSeason) 
        {
            seasonalPlants.push_back(candidate);
        } 

        else 
        {
            double careScore = 0.0;
            for (auto* purchased : purchasedPlants) 
            {
                auto* purchasedFly = dynamic_cast<SpeciesFlyweight*>(purchased->getSpeciesFly());
                if (!purchasedFly) continue;
                
                double waterDiff = std::abs(candidateFly->getWaterSensitivity() - purchasedFly->getWaterSensitivity());
                double insecticideDiff = std::abs(candidateFly->getInsecticideTolerance() - purchasedFly->getInsecticideTolerance());
                double growthDiff = std::abs(candidateFly->getGrowthRate() - purchasedFly->getGrowthRate());
                
                if (waterDiff <= 0.1) careScore += 1.0;
                if (insecticideDiff <= 0.1) careScore += 1.0;
                if (growthDiff <= 0.1) careScore += 1.0;
            }
            
            if (careScore > 0) 
            {
                careSimilarPlants.push_back({candidate, careScore});
            } 
            else 
            {
                otherPlants.push_back(candidate);
            }
        }
    }
    
    std::sort(careSimilarPlants.begin(), careSimilarPlants.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<Plant*> recommendations;
    
    int biomeLimit = std::min(15, static_cast<int>(favoriteBiomePlants.size()));
    recommendations.insert(recommendations.end(), favoriteBiomePlants.begin(), favoriteBiomePlants.begin() + biomeLimit);
    
    if (recommendations.size() < 15 && !seasonalPlants.empty()) 
    {
        int toAdd = std::min(15 - static_cast<int>(recommendations.size()), static_cast<int>(seasonalPlants.size()));
        recommendations.insert(recommendations.end(), seasonalPlants.begin(), seasonalPlants.begin() + toAdd);
    }
    
    if (recommendations.size() < 15 && !careSimilarPlants.empty()) 
    {
        int toAdd = std::min(15 - static_cast<int>(recommendations.size()), static_cast<int>(careSimilarPlants.size()));
        for (int i = 0; i < toAdd; ++i) 
        {
            recommendations.push_back(careSimilarPlants[i].first);
        }
    }
    
    if (recommendations.size() < 15 && !otherPlants.empty()) 
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(otherPlants.begin(), otherPlants.end(), g);
        
        int toAdd = std::min(15 - static_cast<int>(recommendations.size()), static_cast<int>(otherPlants.size()));
        recommendations.insert(recommendations.end(), otherPlants.begin(), otherPlants.begin() + toAdd);
    }
    
    return recommendations;
}

int NurseryFacade::getQueueSize() 
{ 
    return invoker ? invoker->queueSize() : 0; 
}

int NurseryFacade::getRestockHistorySize() 
{ 
    return invoker ? invoker->restockHistorySize() : 0; 
}

bool NurseryFacade::processNextCommand() 
{ 
    return invoker ? invoker->processNext() : false; 
}

int NurseryFacade::processAllCommands() 
{ 
    return invoker ? invoker->processAll() : 0; 
}

bool NurseryFacade::undoLastRestock() 
{ 
    return invoker ? invoker->undoLastRestock() : false; 
}

void NurseryFacade::enqueueWater(std::vector<Plant*>& plants, const std::string& userId)
{
    if (!invoker) return;
    auto cmd = std::make_unique<Water>(plants);
    cmd->setUserId(userId);
    cmd->setAction("WATER");
    cmd->setUndoable(false);
    invoker->enqueue(std::move(cmd));
}

void NurseryFacade::enqueueFertilize(std::vector<Plant*>& plants, const std::string& userId)
{
    if (!invoker) return;
    auto cmd = std::make_unique<Fertilize>(plants);
    cmd->setUserId(userId);
    cmd->setAction("FERTILIZE");
    cmd->setUndoable(false);
    invoker->enqueue(std::move(cmd));
}

void NurseryFacade::enqueueSpray(std::vector<Plant*>& plants, const std::string& userId)
{
    if (!invoker) return;
    auto cmd = std::make_unique<Spray>(plants);
    cmd->setUserId(userId);
    cmd->setAction("SPRAY");
    cmd->setUndoable(false);
    invoker->enqueue(std::move(cmd));
}

void NurseryFacade::enqueueRestock(const std::vector<std::string>& skus, int qty, const std::string& userId)
{
    if (!invoker || !greenhouse || skus.empty()) return;
    
    if (skus.size() == 1)
    {
        auto cmd = std::make_unique<Restock>(*greenhouse, skus[0], qty);
        cmd->setUserId(userId);
        cmd->setAction("RESTOCK");
        cmd->setUndoable(true);
        invoker->enqueue(std::move(cmd));
    }
    else
    {
        auto macro = std::make_unique<MacroCommand>("Batch Restock");
        macro->setUserId(userId);
        macro->setAction("RESTOCK");
        macro->setUndoable(true);
        
        for (const auto& sku : skus)
        {
            auto cmd = std::make_unique<Restock>(*greenhouse, sku, qty);
            cmd->setUserId(userId);
            cmd->setAction("RESTOCK");
            cmd->setUndoable(true);
            macro->addCommand(std::move(cmd));
        }
        
        invoker->enqueue(std::move(macro));
    }
}