#include "CustomerService.h"
#include "MessagingMediator.h"
#include "ChatMediator.h"
#include <memory>

CustomerService::CustomerService(MessagingMediator* med) : mediator(med) {}

void CustomerService::addCustomer(std::string id, std::string name) 
{
    auto customer = std::make_shared<Customer>(mediator, id, name);
    customers[id] = customer;
    if (mediator) 
    {
        ChatMediator* chatMed = dynamic_cast<ChatMediator*>(mediator);
        if (chatMed) 
        {
            chatMed->registerColleague(customer.get());
        }
    }
}

Customer* CustomerService::getCustomer(std::string id) 
{
    auto it = customers.find(id);
    return (it != customers.end()) ? it->second.get() : nullptr;
}

void CustomerService::assignOrderToCustomer(std::string orderId, std::string customerId) 
{
    orderToCustomer[orderId] = customerId;
    auto it = customers.find(customerId);
    if (it != customers.end()) it->second->addActiveOrder(orderId);
}

std::string CustomerService::getCustomerIdByOrder(std::string orderId) 
{
    auto it = orderToCustomer.find(orderId);
    return (it != orderToCustomer.end()) ? it->second : "";
}

std::vector<Customer> CustomerService::getAllCustomers() 
{
    std::vector<Customer> list;
    for (auto& [_, c] : customers)
    {
        list.push_back(*c);
    }
    return list;
}

void CustomerService::setMediator(MessagingMediator* med) 
{ 
    mediator = med; 
}