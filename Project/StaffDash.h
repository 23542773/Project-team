/**
 * @file StaffDash.h
 * @brief Staff Dashboard Observer implementation
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * The StaffDash class implements the NurseryObserver interface to handle
 * various nursery events and update the staff dashboard accordingly.
 */
#ifndef STAFFDASH_H
#define STAFFDASH_H
#include <vector>
#include <string>
#include "NurseryObserver.h"

/**
 * @class StaffDash
 * @brief Concrete Observer implementation for staff dashboard updates
 * @details
 * Handles Plant, Stock, and Order events to generate alerts for staff.
 */
class StaffDash : public NurseryObserver 
{
public:

    /**
     * @brief Handle Plant lifecycle events
     * @param e The Plant event data
     * @returns void
     */
    void onEvent(events::Plant e) override;

    /**
     * @brief Handle Stock events
     * @param s The Stock event data
     * @returns void
     */
    void onEvent(events::Stock s) override;

    /**
     * @brief Handle Order events/alerts currently assigned to staff
     * @param o The Order event data
     * @returns void
     */
    void onEvent(events::Order& o) override;
    std::vector<std::string>& getAlerts();
    void clear();

private:

    /**
     * @brief Get the current alerts for the staff dashboard
     * @returns A vector of alert messages
     */
    std::vector<std::string>& getAlerts();
    void clear();

private:

    /**
     * @brief List of alerts for the staff dashboard
     * @details
     * This vector stores alert messages generated from various events.
     */
    std::vector<std::string> alerts;
};
#endif // STAFFDASH_H