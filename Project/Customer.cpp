#include "Customer.h"

Customer::Customer(MessagingMediator* med, const std::string& custId, const std::string& custName) : Colleague(med, custId), name(custName) {}

void Customer::sendMessage(Colleague* to, const std::string& text) 
{
    if (mediator && to) 
    {
        mediator->sendMessage(this, to, text);
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