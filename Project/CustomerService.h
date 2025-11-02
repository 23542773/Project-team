/**
 * @file CustomerService.h
 * @brief Defines the CustomerService class, responsible for managing customer data and interactions.
 */

#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory> // Required for std::shared_ptr
#include "Customer.h" // Dependent on the Customer class

// Forward declaration of the mediator class
class MessagingMediator;

/**
 * @class CustomerService
 * @brief Manages a collection of Customer objects and tracks their associated orders.
 *
 * This class acts as a service layer for customer data and utilizes a MessagingMediator
 * to handle communications related to customers (e.g., chat functionality).
 */
class CustomerService
{

private:

    /**
     * @brief A map storing all customer objects, indexed by their unique ID.
     * Customers are managed using shared pointers for safe lifetime management.
     */
    std::unordered_map<std::string, std::shared_ptr<Customer>> customers;

    /**
     * @brief A map linking order IDs to the unique ID of the customer who placed the order.
     */
    std::unordered_map<std::string, std::string> orderToCustomer;

    /**
     * @brief A pointer to the central MessagingMediator for customer-related communications.
     */
    MessagingMediator* mediator;

public:

    /**
     * @brief Constructor for CustomerService.
     * @param med A pointer to the MessagingMediator to be used by the service.
     */
    CustomerService(MessagingMediator* med);

    /**
     * @brief Sets or updates the MessagingMediator used by this service.
     * @param med A pointer to the new MessagingMediator.
     */
    void setMediator(MessagingMediator* med);

    /**
     * @brief Creates a new Customer object and adds it to the service's collection.
     * @param id The unique identifier for the new customer.
     * @param name The full name of the new customer.
     */
    void addCustomer(std::string id, std::string name);

    /**
     * @brief Retrieves a customer object by their unique ID.
     * @param id The unique identifier of the customer to retrieve.
     * @return A raw pointer to the requested Customer object, or nullptr if not found.
     */
    Customer* getCustomer(std::string id);

    /**
     * @brief Establishes a link between a specific order ID and a customer ID.
     * @param orderId The unique identifier of the order.
     * @param customerId The unique identifier of the customer who placed the order.
     */
    void assignOrderToCustomer(std::string orderId, std::string customerId);

    /**
     * @brief Retrieves the customer ID associated with a given order ID.
     * @param orderId The unique identifier of the order.
     * @return The unique identifier of the customer, or an empty string if the order is not found.
     */
    std::string getCustomerIdByOrder(std::string orderId);

    /**
     * @brief Retrieves a vector containing copies of all managed Customer objects.
     * @return A vector of Customer objects.
     */
    std::vector<Customer> getAllCustomers();
};

#endif