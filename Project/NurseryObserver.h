#ifndef NURSERYOBSERVER_H
#define NURSERYOBSERVER_H
#include "Events.h"

/// \brief Abstract Base class for Observer hierachy
class NurseryObserver
{
    public:

    /// \brief Reaction to a Plant Event
    virtual void onEvent(events::Plant) = 0;

    /// \brief Reaction to a Stock Event
    virtual void onEvent(events::Stock) {}

    /// \brief Reaction to an Order Event
    virtual void onEvent(events::Order&) {}

    virtual ~NurseryObserver() = default;
};

#endif