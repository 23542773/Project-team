#include "Staff.h"

 

Staff::Staff(MessagingMediator* med, const std::string& staffId, const std::string& staffName, StaffRole staffRole)
    : Colleague(med, staffId), name(staffName), role(staffRole) {}

void Staff::sendMessage(Colleague* to, const std::string& text)  
{
    if (mediator && to) 
    {
        mediator->sendMessage(this, to, text);
    }
}

void Staff::receiveMessage(const Message& msg)  
{
    receivedMessages.push_back(msg);
}

std::vector<Message> Staff::getConversation(const std::string& otherUserId) const 
{
    std::vector<Message> conversation;
    for (const auto& msg : receivedMessages) 
    {
        if (msg.fromUser == otherUserId || msg.toUser == otherUserId)
        {
            conversation.push_back(msg);
        }
    }
    return conversation;
}

std::string Staff::getId() const 
{ 
    return userId; 
}

StaffRole Staff::getRole() const 
{ 
    return role; 
}
