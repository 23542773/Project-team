#include "DummySalesService.h"
#include "DummyOrderItem.h"
#include <iostream>

DummySalesService::DummySalesService() : nextOrderId(1000) {
    std::cout << "[DummySalesService] Initializing with dummy customers...\n";
    
    // TODO: Populate with dummy customers
    customers["CUST-001"] = "John Doe";
    customers["CUST-002"] = "Jane Smith";
    customers["CUST-003"] = "Bob Johnson";
    
    std::cout << "[DummySalesService] Loaded " << customers.size() << " customers\n";
    for (const auto& pair : customers) {
        std::cout << "  - " << pair.first << ": " << pair.second << "\n";
    }
}

DummySalesService::~DummySalesService() {
}

void DummySalesService::addCustomer(const std::string& custId,
                                    const std::string& name) {
    customers[custId] = name;
    std::cout << "[DummySalesService] Added customer: " << custId << " (" << name << ")\n";
}

bool DummySalesService::customerExists(const std::string& custId) const {
    bool exists = customers.find(custId) != customers.end();
    std::cout << "[DummySalesService] Customer " << custId << " exists: " 
              << (exists ? "YES" : "NO") << "\n";
    return exists;
}

std::string DummySalesService::createOrder(const std::string& custId,
                                          const std::vector<OrderItem*>& items) {
    std::string orderId = "ORD-" + std::to_string(nextOrderId++);
    
    std::cout << "[DummySalesService] Creating order " << orderId 
              << " for customer " << custId << "\n";
    std::cout << "  Items: " << items.size() << "\n";
    for (const auto& item : items) {
        std::cout << "    - " << item->id << " @ R" << item->price << "\n";
    }
    
    customerOrders[custId].push_back(orderId);
    orderStatus[orderId] = "PENDING";
    
    std::cout << "[DummySalesService] Order created: " << orderId << "\n";
    
    return orderId;
}

void DummySalesService::updateOrderStatus(const std::string& orderId,
                                         const std::string& status) {
    orderStatus[orderId] = status;
    std::cout << "[DummySalesService] Order " << orderId << " status updated to: " 
              << status << "\n";
}

std::vector<std::string> DummySalesService::getCustomerOrderIds(
    const std::string& custId) const {
    auto it = customerOrders.find(custId);
    if (it != customerOrders.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

std::string DummySalesService::getOrderStatus(const std::string& orderId) const {
    auto it = orderStatus.find(orderId);
    if (it != orderStatus.end()) {
        return it->second;
    }
    return "UNKNOWN";
}