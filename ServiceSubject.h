#ifndef SERVICESUBJECT_H
#define SERVICESUBJECT_H
#include "NurseryObserver.h"
class Subject 
{

protected:

    /// \brief References to the Observers
    NurseryObserver* hub = nullptr;
    NurseryObserver* dash = nullptr;

    /// \brief Notify Observers of specific events
    void notify(events::Order& e);
    void notify(events::Stock& e);
    void notify(events::Plant& e);

public:

    virtual ~ServiceSubject() = 0;
    /// \brief Set Observers
    void setObservers(NurseryObserver* hub, NurseryObserver* dash);
};
#endif