#ifndef MESSAGING_MEDIATOR_H
#define MESSAGING_MEDIATOR_H
#include <string>
#include <vector>
#include "Message.h"

class Colleague;

class MessagingMediator 
{
public:

    virtual ~MessagingMediator() = default;

    virtual void sendMessage(Colleague* from, Colleague* to, const std::string& text) = 0;

};

#endif
