#include "StaffDash.h"

void StaffDash::onEvent(events::Plant e) 
{
    if (e.type == events::PlantType::Wilted) alerts.push_back("Plant wilted: " + e.plantId);
    else if (e.type == events::PlantType::Matured) alerts.push_back("Plant matured: " + e.plantId);
}
void StaffDash::onEvent(events::Stock s) 
{
    if (s.type == events::StockType::Added) alerts.push_back("Stock added for SKU: " + s.key);
}
void StaffDash::onEvent(events::Order& o) 
{
    if (o.type == events::OrderType::Created) alerts.push_back("New order: " + o.orderId);
}

std::vector<std::string>& StaffDash::getAlerts() 
{ 
    return alerts; 
}

void StaffDash::clear() 
{ 
    alerts.clear(); 
}