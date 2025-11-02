/**
 * @file ServiceSubject.cpp
 * @brief Implementation of ServiceSubject methods (Observer Pattern)
 * @author Damian Moustakis(Doxygen comments)
 * @date 2025-11-01
 * @details
 * Implements the notification mechanisms for the Subject in the Observer pattern,
 * allowing it to inform registered NurseryObservers of various events:
 * - Plant Events: Lifecycle changes in plants
 * - Stock Events: Inventory level changes
 * - Order Events: Order lifecycle changes
 */
#include "ServiceSubject.h"
#include "Events.h"

/**
 * @brief Notify all observers of a Plant lifecycle event
 * @param e The Plant event data (ID, SKU and event type)
 * @returns void
 */
void ServiceSubject::notify(events::Plant e) 
{ 
    for (auto* obs : observers) 
    {
        if (obs) obs->onEvent(e);
    }
}

/**
 * @brief Notify all observers of a Stock event
 * @param s The Stock event data SKU and event type
 * @returns void
 */
void ServiceSubject::notify(events::Stock s)
{
    for (auto* obs : observers) 
    {
        if (obs) obs->onEvent(s);
    }
}

/**
 * @brief Notify all observers of an Order event
 * @param o The Order event data, passed by reference
 * @returns void
 */
void ServiceSubject::notify(events::Order& o)
{
    for (auto* obs : observers) 
    {
        if (obs) obs->onEvent(o);
    }
}

/**
 * @brief Add an observer to the subject's observer list
 * @param obs Pointer to the observer to add
 * @returns void
 */
void ServiceSubject::addObserver(NurseryObserver* obs)
{
    if (obs) observers.push_back(obs);
}

/**
 * @brief Alternate to registering Observer roles
 * @param inv Pointer to the observer to set
 * @returns void
 */
void ServiceSubject::setObservers(NurseryObserver* inv) 
{ 
    addObserver(inv); 
}

/**
 * @brief Virtual destructor
 * @returns void
 */
ServiceSubject::~ServiceSubject() = default;