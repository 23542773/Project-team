/**
 * @file ServiceSubject.h
 * @brief Defines the abstract Subject base class for event emitters in the Nursery system (Observer Pattern).
 */

#ifndef SERVICESUBJECT_H
#define SERVICESUBJECT_H
#include <vector>
#include "NurseryObserver.h"
#include "Events.h"

/**
 * @class ServiceSubject
 * @brief An abstract Subject that maintains a list of interested NurseryObserver objects and notifies them of events.
 *
 * Concrete service classes (like Greenhouse or SalesService) inherit from this class to gain
 * event-emitting capabilities, implementing the 'one-to-many' dependency defined by the Observer pattern.
 */

class ServiceSubject 
{

protected:

    /**
     * @brief A collection of raw pointers to the currently registered NurseryObserver objects.
     */

    std::vector<NurseryObserver*> observers;

    /**
     * @brief Notifies all registered observers of a Plant event.
     *
     * Iterates through the observers and calls their `onEvent(events::Plant)` method.
     *
     * @param e The Plant event data structure to send.
     */

    void notify(events::Plant e);

    /**
     * @brief Notifies all registered observers of a Stock event.
     *
     * Iterates through the observers and calls their `onEvent(events::Stock)` method.
     *
     * @param s The Stock event data structure to send.
     */

    void notify(events::Stock s);

    /**
     * @brief Notifies all registered observers of an Order event.
     *
     * Iterates through the observers and calls their `onEvent(events::Order&)` method.
     *
     * @param o A reference to the Order event data structure to send.
     */

    void notify(events::Order& o);

public:

/**
 * @brief Virtual destructor to ensure proper cleanup of derived concrete subject classes.
 */

    virtual ~ServiceSubject();

    /**
     * @brief Registers a new observer to receive future event notifications.
     * @param obs A pointer to the NurseryObserver object to be added.
     */

    void addObserver(NurseryObserver* obs);
    
    /**
     * @brief Sets the list of observers to contain only a single, specific observer.
     * @param inv A pointer to the single NurseryObserver to be set.
     */

    void setObservers(NurseryObserver* inv);
};
#endif