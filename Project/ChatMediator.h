#ifndef CHAT_MEDIATOR_H
#define CHAT_MEDIATOR_H
#include <vector>
#include "MessagingMediator.h"

class Colleague;
class Staff;

class ChatMediator : public MessagingMediator 
{
public:

    ChatMediator();

    void sendMessage(Colleague* from, Colleague* to, const std::string& text) override;

    void registerColleague(Colleague* colleague);

    void unregisterColleague(Colleague* colleague);

private:

    std::vector<Colleague*> colleagues;
    unsigned long seq = 1;

    bool isCustomer(Colleague* colleague) const;
    bool isStaff(Colleague* colleague) const;
    Staff* asStaff(Colleague* colleague) const;
};

#endif
