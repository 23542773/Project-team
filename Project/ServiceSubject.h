#ifndef SERVICESUBJECT_H
#define SERVICESUBJECT_H
#include "NurseryObserver.h"
class ServiceSubject 
{

protected:

    /// \brief References to the Observers
    NurseryObserver* inv = nullptr;

    /// \brief Notify Observers of specific events
    void notify(events::Plant e);

public:

    virtual ~ServiceSubject();
    /// \brief Set Observers
    void setObservers(NurseryObserver* inv);
};
#endif