#ifndef CHAT_MEDIATOR_H
#define CHAT_MEDIATOR_H
#include <vector>
#include <unordered_map>
#include "MessagingMediator.h"

class Colleague;
class Staff;

class ChatMediator : public MessagingMediator 
{
public:

    ChatMediator();

    void sendMessageToId(Colleague* from, const std::string& toUserId, const std::string& text) override;

    void registerColleague(Colleague* colleague);

    void unregisterColleague(Colleague* colleague);

private:

    std::vector<Colleague*> colleagues;
    std::unordered_map<std::string, Colleague*> indexById;
    unsigned long seq = 1;

    void sendMessage(Colleague* from, Colleague* to, const std::string& text);

    bool isCustomer(Colleague* colleague) const;
    bool isStaff(Colleague* colleague) const;
    Staff* asStaff(Colleague* colleague) const;
};

#endif
