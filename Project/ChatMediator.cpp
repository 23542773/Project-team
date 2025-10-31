#include "ChatMediator.h"
#include "Staff.h"
#include "Customer.h"
#include "Colleague.h"
#include <algorithm>
#include <ctime>

ChatMediator::ChatMediator() {}

void ChatMediator::registerColleague(Colleague* colleague) 
{
    if (colleague) 
    {
        colleagues.push_back(colleague);
    }
}

void ChatMediator::unregisterColleague(Colleague* colleague) 
{
    colleagues.erase(std::remove(colleagues.begin(), colleagues.end(), colleague), colleagues.end());
}

bool ChatMediator::isCustomer(Colleague* colleague) const 
{
    return dynamic_cast<Customer*>(colleague) != nullptr;
}

bool ChatMediator::isStaff(Colleague* colleague) const 
{
    return dynamic_cast<Staff*>(colleague) != nullptr;
}

Staff* ChatMediator::asStaff(Colleague* colleague) const 
{
    return dynamic_cast<Staff*>(colleague);
}

void ChatMediator::sendMessage(Colleague* from, Colleague* to, const std::string& text) 
{
    if (!from || !to) return;

    bool fromIsCustomer = isCustomer(from);
    bool toIsCustomer = isCustomer(to);
    bool fromIsStaff = isStaff(from);
    bool toIsStaff = isStaff(to);

    if (fromIsCustomer && toIsStaff) 
    {
        Staff* recipient = asStaff(to);
        if (recipient && recipient->getRole() != StaffRole::Sales) 
        {
            return; 
        }
    }
    
    if (fromIsStaff && toIsCustomer) 
    {
        Staff* sender = asStaff(from);
        if (sender && sender->getRole() != StaffRole::Sales) 
        {
            return; 
        }
    }
    
    //Sales <-> Sales
    //PlantCare <-> Inventory
    //Inventory <-> Sales
    if (fromIsStaff && toIsStaff) 
    {
        Staff* sender = asStaff(from);
        Staff* recipient = asStaff(to);
        if (sender && recipient)
        {
            StaffRole senderRole = sender->getRole();
            StaffRole recipientRole = recipient->getRole();

            auto allowed = [&](StaffRole a, StaffRole b) 
            {
                if (a == StaffRole::Sales && b == StaffRole::Sales) return true;

                if ((a == StaffRole::PlantCare && b == StaffRole::Inventory) ||
                    (a == StaffRole::Inventory && b == StaffRole::PlantCare)) return true;

                if ((a == StaffRole::Inventory && b == StaffRole::Sales) ||
                    (a == StaffRole::Sales && b == StaffRole::Inventory)) return true;
                    
                return false;
            };

            if (!allowed(senderRole, recipientRole))
            {
                return;
            }
        }
    }
    
    Message m;
    m.id = std::to_string(seq++);
    m.fromUser = from->getUserId();
    m.toUser = to->getUserId();
    m.text = text;
    m.timestamp = std::time(nullptr);
    
    //Push to both sender and receiver
    from->receiveMessage(m);
    to->receiveMessage(m);
}