#include "StaffService.h"

void StaffService::addStaff(std::string id, std::string name)
{
    staffMap[id] = {id, name, {}, true};
}

std::string StaffService::leastLoaded()
{
    std::string best;
    int minLoad = INT_MAX;

    for (auto& [id, s] : staffMap)
    {
        int load = static_cast<int>(s.assignedOrders.size());
        if (!s.available && load > 0) continue; 

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

    it->second.assignedOrders.push_back(orderId);
    it->second.available = false;
}

void StaffService::completeOrder(std::string orderId)
{
    for (auto& [id, s] : staffMap)
    {
        auto it = std::find(s.assignedOrders.begin(), s.assignedOrders.end(), orderId);

        if (it != s.assignedOrders.end())
        {
            s.assignedOrders.erase(it);
            if (s.assignedOrders.empty()) s.available = true;
            return;
        }
    }
}

bool StaffService::isAvailable(std::string staffId)
{
    auto it = staffMap.find(staffId);
    return it != staffMap.end() && it->second.available;
}

Staff* StaffService::get(std::string staffId)
{
	auto it = staffMap.find(staffId);
	if (it == staffMap.end()) return nullptr;
	return &it->second;
}

std::vector<std::string> StaffService::getOrdersForStaff(std::string staffId)
{
	auto it = staffMap.find(staffId);
    if (it == staffMap.end()) return {};
    return it->second.assignedOrders;
}

std::vector<StaffService::Staff> StaffService::listStaff()
{
    std::vector<Staff> result;
    for (auto& [id, s] : staffMap) result.push_back(s);
    return result;
}
