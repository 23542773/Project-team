#include "ServiceSubject.h"

void ServiceSubject::notify(events::Order& e) 
{ 
    if (hub) hub->onEvent(e); 
    if (dash) dash->onEvent(e); 
}

void ServiceSubject::notify(events::Stock& e) 
{ 
    if (hub) hub->onEvent(e); 
    if (dash) dash->onEvent(e); 
}

void ServiceSubject::notify(events::Plant& e) 
{ 
    if (hub) hub->onEvent(e); 
    if (dash) dash->onEvent(e); 
}

void ServiceSubject::setObservers(NurseryObserver* hub, NurseryObserver* dash)
{
    this->hub = hub;
    this->dash = dash; 
}