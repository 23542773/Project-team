#ifndef COLLEAGUE_H
#define COLLEAGUE_H

#include <string>

class MessagingMediator;
struct Message;

class Colleague 
{
protected:

    MessagingMediator* mediator;
    std::string userId;

public:
    Colleague(MessagingMediator* med, const std::string& id) : mediator(med), userId(id) {}
    
    virtual ~Colleague() = default;

    virtual void sendMessage(Colleague* to, const std::string& text) = 0;

    virtual void receiveMessage(const Message& msg) = 0;

    std::string getUserId() const { return userId; }
};

#endif
