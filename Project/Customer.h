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
    std::string name;
    std::vector<std::string> activeOrders;

public:

    Customer(MessagingMediator* med, const std::string& customerId, const std::string& customerName);

    void sendMessage(const std::string& toUserId, const std::string& text) override;

    void receiveMessage(const Message& msg) override;

    std::vector<Message> getConversation(const std::string& otherUserId) const;

    std::string getId() const;

    std::string getName() const;

    const std::vector<std::string>& getActiveOrders() const;

    void addActiveOrder(const std::string& orderId);
};

#endif
