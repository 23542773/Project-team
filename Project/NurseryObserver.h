/**
 * @file NurseryObserver.h
 * @brief Abstract Base class for Observer hierarchy
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * Defines the interface for all Observers in the Nursery system,
 * enforcing implementation of Plant event handling, with
 * optional overrides for Stock and Order event handling.
 */
#ifndef NURSERYOBSERVER_H
#define NURSERYOBSERVER_H
#include "Events.h"

/**
 * @class NurseryObserver
 * @brief Abstract Base class for all Observers in the Nursery system
 * @details Defines the interface for handling different event types:
 * - Plant Events: Pure virtual method to enforce implementation in derived classes
 * - Stock Events: Default empty implementation, can be overridden
 * - Order Events: Default empty implementation, can be overridden
 */
class NurseryObserver
{
    public:

    /**
     * @brief Handle plant lifecycle events
     * @param event The Plant event data
     * @returns void
     */
    virtual void onEvent(events::Plant) = 0;

    /**
     * @brief Reaction to a Stock Event
     * @param event The Stock event data
     * @returns void
     */
    virtual void onEvent(events::Stock) {}

    /**
     * @brief Reaction to an Order Event
     * @param event The Order event data
     * @returns void
     */
    virtual void onEvent(events::Order&) {}

    /**
     * @brief Virtual destructor
     * @returns void
     */
    virtual ~NurseryObserver() = default;
};

#endif // NURSERYOBSERVER_H