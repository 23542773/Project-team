#include "Customer.h"

Customer::Customer(MessagingMediator* med, const std::string& custId, const std::string& custName) : Colleague(med, custId), name(custName) {}

void Customer::sendMessage(const std::string& toUserId, const std::string& text) 
{
    if (mediator) 
    {
        mediator->sendMessageToId(this, toUserId, text);
    }
}

void Customer::receiveMessage(const Message& msg) 
{
    receivedMessages.push_back(msg);
}

std::vector<Message> Customer::getConversation(const std::string& otherUserId) const 
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

std::string Customer::getId() const 
{ 
    return userId; 
}

std::string Customer::getName() const 
{ 
    return name; 
}

const std::vector<std::string>& Customer::getActiveOrders() const 
{ 
    return activeOrders; 
}

void Customer::addActiveOrder(const std::string& orderId) 
{
    activeOrders.push_back(orderId);
}