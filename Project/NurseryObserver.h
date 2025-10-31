#ifndef NURSERYOBSERVER_H
#define NURSERYOBSERVER_H
#include "Events.h"

/// \brief Abstract Base class for Observer hierachy
class NurseryObserver
{
    public:

    /// \brief Reaction to a Plant Event
    virtual void onEvent(events::Plant) = 0;

    virtual ~NurseryObserver() = default;
};

#endif