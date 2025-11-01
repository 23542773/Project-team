#ifndef SERVICESUBJECT_H
#define SERVICESUBJECT_H
#include <vector>
#include "NurseryObserver.h"
#include "Events.h"
class ServiceSubject 
{

protected:

    /// \brief References to the Observers
    std::vector<NurseryObserver*> observers;

    /// \brief Notify Observers of specific events
    void notify(events::Plant e);
    void notify(events::Stock s);
    void notify(events::Order& o);

public:

    virtual ~ServiceSubject();
    /// \brief Add an observer
    void addObserver(NurseryObserver* obs);
    void setObservers(NurseryObserver* inv);
};
#endif