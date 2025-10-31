#include "StaffService.h"
#include "MessagingMediator.h"
#include "ChatMediator.h"
#include <memory>

StaffService::StaffService(MessagingMediator* med) : mediator(med) {}

void StaffService::setMediator(MessagingMediator* med)
{ 
    mediator = med; 
}

void StaffService::addStaff(std::string id, std::string name, StaffRole role)
{
    auto staff = std::make_shared<Staff>(mediator, id, name, role);
    staffMap[id] = staff;
    
    if (mediator) 
    {
        ChatMediator* chatMed = dynamic_cast<ChatMediator*>(mediator);
        if (chatMed) 
        {
            chatMed->registerColleague(staff.get());
        }
    }
}

std::string StaffService::leastLoaded()
{
    std::string best;
    int minLoad = INT_MAX;

    for (auto& [id, s] : staffMap)
    {
        if (s->getRole() != StaffRole::Sales) continue;
        
        int load = static_cast<int>(s->assignedOrders.size());
        if (!s->available && load > 0) continue; 

        if (load < minLoad)
        {
            best = id;
            minLoad = load;
        }
    }
    return best;
}

void StaffService::assignOrder(std::string staffId, std::string orderId)
{
    auto it = staffMap.find(staffId);
    if (it == staffMap.end()) return;

    it->second->assignedOrders.push_back(orderId);
    const int maxOrdersPerStaff = 5; 
    if (it->second->assignedOrders.size() >= maxOrdersPerStaff) it->second->available = false;
}

void StaffService::completeOrder(std::string orderId)
{
    for (auto& [id, s] : staffMap)
    {
        auto it = std::find(s->assignedOrders.begin(), s->assignedOrders.end(), orderId);

        if (it != s->assignedOrders.end())
        {
            s->assignedOrders.erase(it);
            return;
        }
    }
}

bool StaffService::isAvailable(std::string staffId)
{
    auto it = staffMap.find(staffId);
    return it != staffMap.end() && it->second->available;
}

Staff* StaffService::getStaff(std::string staffId)
{
	auto it = staffMap.find(staffId);
	if (it == staffMap.end()) return nullptr;
	return it->second.get();
}

std::vector<std::string> StaffService::getOrdersForStaff(std::string staffId)
{
	auto it = staffMap.find(staffId);
    if (it == staffMap.end()) return {};
    return it->second->assignedOrders;
}

std::vector<Staff> StaffService::listStaff()
{
    std::vector<Staff> result;
    for (auto& [id, s] : staffMap) result.push_back(*s);
    return result;
}
