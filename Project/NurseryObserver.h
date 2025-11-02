/**
 * @file NurseryObserver.h
 * @brief Defines the abstract base class for all Observers in the Nursery event system.
 */

#ifndef NURSERYOBSERVER_H
#define NURSERYOBSERVER_H
#include "Events.h"

/**
 * @class NurseryObserver
 * @brief The abstract interface for Observer objects that subscribe to events emitted by Nursery subjects (like Greenhouse, OrderService).
 *
 * This class defines a set of overloaded virtual functions, allowing concrete observers
 * to selectively react to different types of system events (Plant, Stock, Order).
 */
class NurseryObserver
{
    public:

    /**
     * @brief The mandatory reaction method for Plant events.
     *
     * This is a pure virtual function and must be implemented by all concrete observers.
     *
     * @param event The Plant event data structure.
     */

    virtual void onEvent(events::Plant) = 0;

    /**
     * @brief Optional reaction method for Stock events.
     *
     * Provides a default empty implementation. Concrete observers can override this to
     * handle stock status changes.
     *
     * @param event The Stock event data structure.
     */
    virtual void onEvent(events::Stock) {}

    /**
     * @brief Optional reaction method for Order events.
     *
     * Provides a default empty implementation. Concrete observers can override this to
     * handle lifecycle changes of orders.
     *
     * @param event A reference to the Order event data structure.
     */

    virtual void onEvent(events::Order&) {}

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived concrete observer classes.
     */

    virtual ~NurseryObserver() = default;
};

#endif