/**
 * @file StaffDash.h
 * @brief Defines the StaffDash class, a concrete Observer that monitors and logs various
 * Plant, Stock, and Order events as actionable alerts for staff.
 */

#ifndef STAFFDASH_H
#define STAFFDASH_H
#include <vector>
#include <string>
#include "NurseryObserver.h"

/**
 * @class StaffDash
 * @brief Represents a staff dashboard component that subscribes to all types of events
 * from the Nursery Subject(s).
 *
 * It overrides all three `onEvent` methods defined in `NurseryObserver`, collecting
 * relevant information into a list of alerts for staff action or review.
 */


class StaffDash : public NurseryObserver 
{
public:
    /**
     * @brief Reaction method for Plant events (e.g., Matured, Wilted, Died).
     *
     * Processes the event and generates an alert for staff based on the plant's status change.
     *
     * @param e The Plant event data structure.
     */

    void onEvent(events::Plant e) override;
    /**
     * @brief Reaction method for Stock events (e.g., Low Stock).
     *
     * Processes the event and generates a restocking or inventory-related alert for staff.
     *
     * @param s The Stock event data structure.
     */

    void onEvent(events::Stock s) override;

    /**
     * @brief Reaction method for Order events (e.g., New Order Created, Order Cancelled).
     *
     * Processes the event and generates an order fulfillment or status alert for staff.
     *
     * @param o A reference to the Order event data structure.
     */

    void onEvent(events::Order& o) override;

    /**
     * @brief Retrieves the list of all collected staff alerts.
     * @return A reference to the vector containing the generated alert messages.
     */


    std::vector<std::string>& getAlerts();

    /**
     * @brief Clears the internal list of collected staff alerts.
     */

    void clear();

private:
    /**
     * @brief Stores a collection of human-readable alert messages generated from processed events.
     */

    std::vector<std::string> alerts;
};
#endif
