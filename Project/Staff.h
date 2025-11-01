#ifndef STAFF_H
#define STAFF_H

#include "Colleague.h"
#include "MessagingMediator.h"
#include "Message.h"
#include <vector>
#include <string>
#include <algorithm>


enum class StaffRole 
{
    PlantCare,      
    Inventory,    
    Sales          
};


class Staff : public Colleague 
{

private:

    std::vector<Message> receivedMessages;
    std::string name;
    std::vector<std::string> assignedOrders;
    bool available = true;
    StaffRole role;

public:

    Staff(MessagingMediator* med, const std::string& staffId, const std::string& staffName, StaffRole staffRole = StaffRole::Sales);

    void sendMessage(const std::string& toUserId, const std::string& text) override;

    void receiveMessage(const Message& msg) override;

    std::vector<Message> getConversation(const std::string& otherUserId) const;

    std::string getId() const;

    StaffRole getRole() const;

    std::string getName() const;

    const std::vector<std::string>& getAssignedOrders() const;

    bool isAvailable() const;

    void addAssignedOrder(const std::string& orderId);

    void removeAssignedOrder(const std::string& orderId);
    
    void setAvailable(bool avail);
};

#endif
