#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Colleague.h"
#include "MessagingMediator.h"
#include "Message.h"
#include <vector>
#include <string>

class Customer : public Colleague 
{
private:
    std::vector<Message> receivedMessages;

public:

    std::string name;
    std::vector<std::string> activeOrders;

    Customer(MessagingMediator* med, const std::string& customerId, const std::string& customerName);

    void sendMessage(Colleague* to, const std::string& text) override;

    void receiveMessage(const Message& msg) override;

    std::vector<Message> getConversation(const std::string& otherUserId) const;

    std::string getId() const;
};

#endif
