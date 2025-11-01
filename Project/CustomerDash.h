/**
 * @file CustomerDash.h
 * @brief Customer Dashboard Observer implementation
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * The CustomerDash class implements the NurseryObserver interface to handle
 * plant growth events and update the customer dashboard.
 */
#ifndef CUSTOMERDASH_H
#define CUSTOMERDASH_H
#include <vector>
#include <string>
#include "NurseryObserver.h"

/**
 * @class CustomerDash
 * @brief Concrete Observer implementation for customer dashboard updates
 * @details
 * Handles Plant events to notify customers of matured plants.
 */
class CustomerDash : public NurseryObserver 
{
public:

    /**
     * @brief Handle Plant lifecycle events
     * @param e The Plant event data
     * @returns void
     */
    void onEvent(events::Plant e) override;

    /**
     * @brief Get the list of matured plant IDs for the customer dashboard
     * @returns A vector of matured plant IDs
     */
    std::vector<std::string>& getMatured();

    /**
     * @brief Clear the list of matured plant IDs
     * @returns void
     */
    void clear();

private:
    
    /**
     * @brief List of matured plant IDs for the customer dashboard
     * @details
     * This vector stores the IDs of plants that have matured.
     */
    std::vector<std::string> maturedIds;
};
#endif // CUSTOMERDASH_H


