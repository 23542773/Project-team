#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Customer.h"

class MessagingMediator;

class CustomerService 
{

private:

    std::unordered_map<std::string, std::shared_ptr<Customer>> customers;
    std::unordered_map<std::string, std::string> orderToCustomer;
    MessagingMediator* mediator;

public:

    CustomerService(MessagingMediator* med);
    void setMediator(MessagingMediator* med);

    void addCustomer(std::string id, std::string name);
    Customer* getCustomer(std::string id);

    void assignOrderToCustomer(std::string orderId, std::string customerId);
    std::string getCustomerIdByOrder(std::string orderId);

    std::vector<Customer> getAllCustomers();
};

#endif
