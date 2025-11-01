#include "Staff.h"

 

Staff::Staff(MessagingMediator* med, const std::string& staffId, const std::string& staffName, StaffRole staffRole)
    : Colleague(med, staffId), name(staffName), role(staffRole) {}

void Staff::sendMessage(const std::string& toUserId, const std::string& text)  
{
    if (mediator) 
    {
        mediator->sendMessageToId(this, toUserId, text);
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

std::string Staff::getName() const 
{ 
    return name; 
}

const std::vector<std::string>& Staff::getAssignedOrders() const 
{ 
    return assignedOrders; 
}
bool Staff::isAvailable() const 
{ 
    return available; 
}

void Staff::addAssignedOrder(const std::string& orderId) 
{ 
    assignedOrders.push_back(orderId); 
}

void Staff::removeAssignedOrder(const std::string& orderId) 
{
    auto it = std::find(assignedOrders.begin(), assignedOrders.end(), orderId);
    if (it != assignedOrders.end()) assignedOrders.erase(it);
}

void Staff::setAvailable(bool avail) 
{ 
    available = avail; 
}