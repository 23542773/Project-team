#ifndef NURSERYOBSERVER_H
#define NURSERYOBSERVER_H
#include "Events.h"

/// \brief Abstract Base class for Observer hierachy
class NurseryObserver
{
    public:

    virtual ~NurseryObserver() = 0;

    /// \brief Reaction to an Order event
    virtual void onEvent(events::Order&) = 0;

    /// \brief Reaction to a Stock Event
    virtual void onEvent(events::Stock&) = 0;

    /// \brief Reaction to a Plant Event
    virtual void onEvent(events::Plant&) = 0;
};

#endif