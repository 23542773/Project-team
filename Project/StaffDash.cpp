/**
 * @file StaffDash.cpp
 * @brief Implementation of StaffDash Observer methods
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * Implements the StaffDash class methods to handle various nursery events
 * and updates the dashboard for the staff.
 */
#include "StaffDash.h"

/**
 * @brief Handle Plant lifecycle events
 * @param e The Plant event data ID, SKU and event type
 * @returns void
 */
void StaffDash::onEvent(events::Plant e) 
{
    if (e.type == events::PlantType::Wilted) alerts.push_back("Plant wilted: " + e.plantId);
    else if (e.type == events::PlantType::Matured) alerts.push_back("Plant matured: " + e.plantId);
}

/**
 * @brief Handle Stock event changes
 * @param s The Stock event data SKU and event type
 * @returns void
 */
void StaffDash::onEvent(events::Stock s) 
{
    if (s.type == events::StockType::Low) alerts.push_back("Stock low for SKU: " + s.key);
}

/**
 * @brief Handle Order events/alerts currently assigned to staff
 * @param o The Order event data
 * @returns void
 */
void StaffDash::onEvent(events::Order& o) 
{
    if (o.type == events::OrderType::Created) alerts.push_back("New order: " + o.orderId);
}

/**
 * @brief Get the current alerts for the staff dashboard
 * @returns A vector of alert messages
 */
std::vector<std::string>& StaffDash::getAlerts() 
{ 
    return alerts; 
}

/**
 * @brief Clear all alerts from the staff dashboard
 * @returns void
 */
void StaffDash::clear() 
{ 
    alerts.clear(); 
}