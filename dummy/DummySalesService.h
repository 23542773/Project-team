#ifndef DUMMY_SALESSERVICE_H
#define DUMMY_SALESSERVICE_H

#include <map>
#include <string>
#include <vector>

/**
 * @file dummy/DummySalesService.h
 * @brief Standalone dummy SalesService for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real SalesService implementation
 */

// Forward declaration
struct DummyOrderItem;

/**
 * @class DummySalesService
 * @brief Standalone dummy sales service - NO INHERITANCE
 * 
 * When real SalesService is ready, change this to inherit from SalesService.
 */
class DummySalesService {
private:
    std::map<std::string, std::string> customers;
    std::map<std::string, std::vector<std::string>> customerOrders;
    std::map<std::string, std::string> orderStatus;
    int nextOrderId;

public:
    /**
     * @brief Constructor - automatically populates with dummy customers
     * 
     * Initializes with customers:
     * - CUST-001: John Doe
     * - CUST-002: Jane Smith
     * - CUST-003: Bob Johnson
     */
    DummySalesService();

    ~DummySalesService();

    /**
     * @brief Add a customer
     * @param custId Customer ID
     * @param name Customer name
     */
    void addCustomer(const std::string& custId, const std::string& name);

    /**
     * @brief Check if customer exists
     * @param custId Customer ID
     * @return true if customer exists
     */
    bool customerExists(const std::string& custId) const;

    /**
     * @brief Create a new order
     * @param custId Customer ID
     * @param items Vector of DummyOrderItems
     * @return Order ID
     */
    std::string createOrder(const std::string& custId,
                           const std::vector<DummyOrderItem*>& items);

    /**
     * @brief Update order status
     * @param orderId Order ID
     * @param status New status
     */
    void updateOrderStatus(const std::string& orderId, const std::string& status);

    /**
     * @brief Get customer order IDs
     * @param custId Customer ID
     * @return Vector of order IDs for this customer
     */
    std::vector<std::string> getCustomerOrderIds(const std::string& custId) const;

    /**
     * @brief Get order status
     * @param orderId Order ID
     * @return Order status string
     */
    std::string getOrderStatus(const std::string& orderId) const;
};

#endif // DUMMY_SALESSERVICE_H