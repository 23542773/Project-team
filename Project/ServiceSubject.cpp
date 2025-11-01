#include "ServiceSubject.h"
#include "Events.h"

void ServiceSubject::notify(events::Plant e) 
{ 
    for (auto* obs : observers) 
    {
        if (obs) obs->onEvent(e);
    }
}

void ServiceSubject::notify(events::Stock s)
{
    for (auto* obs : observers) 
    {
        if (obs) obs->onEvent(s);
    }
}

void ServiceSubject::notify(events::Order& o)
{
    for (auto* obs : observers) 
    {
        if (obs) obs->onEvent(o);
    }
}

void ServiceSubject::addObserver(NurseryObserver* obs)
{
    if (obs) observers.push_back(obs);
}

void ServiceSubject::setObservers(NurseryObserver* inv) 
{ 
    addObserver(inv); 
}

ServiceSubject::~ServiceSubject() = default;