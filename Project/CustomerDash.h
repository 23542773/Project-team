/**
 * @file CustomerDash.h
 * @brief Defines the CustomerDash class, a concrete Observer that tracks plant maturation events.
 */

#ifndef CUSTOMERDASH_H
#define CUSTOMERDASH_H

#include <vector>
#include <string>
#include "NurseryObserver.h" // Inherits from the abstract Observer class

/**
 * @class CustomerDash
 * @brief Represents a customer dashboard or interface component that subscribes to
 * notifications from a "Nursery" Subject.
 *
 * It specifically monitors for plant-related events and logs the IDs of plants
 * that have matured. This is a concrete implementation of the NurseryObserver.
 */
class CustomerDash : public NurseryObserver
{
public:

    /**
     * @brief The update method called by the Subject (Nursery) when an event occurs.
     *
     * This method processes the event, typically logging the plant's ID if it
     * meets a specific criteria (e.g., reaching maturity).
     *
     * @param e The Plant event data structure.
     */
    void onEvent(events::Plant e) override;

    /**
     * @brief Retrieves the list of plant IDs that have been recorded as matured.
     * @return A reference to the vector containing the IDs of matured plants.
     */
    std::vector<std::string>& getMatured();

    /**
     * @brief Clears the internal list of matured plant IDs.
     */
    void clear();

private:

    /**
     * @brief Stores the unique identifiers (IDs) of plants that have been reported
     * as having matured via the onEvent method.
     */
    std::vector<std::string> maturedIds;
};

#endif
