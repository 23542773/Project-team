#include "ServiceSubject.h"

void ServiceSubject::notify(events::Plant e) 
{ 
    if (inv) inv->onEvent(e);
}

void ServiceSubject::setObservers(NurseryObserver* inv)
{ 
    this->inv = inv;
}

ServiceSubject::~ServiceSubject() = default;