/**
 * @file ServiceSubject.h
 * @brief Base class for Subjects in the Observer pattern
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * Defines the ServiceSubject class which manages a list of NurseryObservers
 * and notifies them of various events:
 * - Plant Events: Lifecycle changes in plants
 * - Stock Events: Inventory level changes
 * - Order Events: Order lifecycle changes
 */
#ifndef SERVICESUBJECT_H
#define SERVICESUBJECT_H
#include <vector>
#include "NurseryObserver.h"
#include "Events.h"

/**
 * @class ServiceSubject
 * @brief Base class for all Subjects in the Observer pattern
 */
class ServiceSubject 
{

protected:

    /**
     * @brief List of observers "listening" to this subject
     * @details
     * This vector holds pointers to all registered NurseryObservers
     * that will be notified of events.
     */
    std::vector<NurseryObserver*> observers;

    /**
     * @brief Notify all observers of a Plant event
     * @param e The Plant event data
     * @returns void
     */
    void notify(events::Plant e);
    /**
     * @brief Notify all observers of a Stock event
     * @param s The Stock event data
     * @returns void
     */
    void notify(events::Stock s);
    /**
     * @brief Notify all observers of an Order event
     * @param o The Order event data
     * @returns void
     */
    void notify(events::Order& o);

public:

    /**
     * @brief Virtual destructor
     * @details
     */
    virtual ~ServiceSubject();

    /**
     * @brief Add an observer
     * @param obs Pointer to the observer to add
     * @returns void
     */
    void addObserver(NurseryObserver* obs);

    /**
     * @brief Alternate to registering Observer roles
     * @param inv Pointer to the observer to set
     * @returns void
     */
    void setObservers(NurseryObserver* inv);
};
#endif // SERVICESUBJECT_H