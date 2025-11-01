/**
 * @file SalesService.cpp
 * @brief Implementation of SalesService Observer methods
 * @author Damian Moustakis (Doxygen comments)
 * @date 2025-11-01
 * @details
 * Implements the SalesService class methods to handle sales-related
 * events and data.
 */
#include "SalesService.h"
#include <sstream>
#include <iomanip>
using events::Order;
using events::OrderLine;
using events::OrderType;
using events::OrderStatus;

/**
 * @brief Generates the next unique order ID
 * @returns The next order ID as a string
 */
std::string SalesService::nextOrderId() 
{
    std::ostringstream os;
    os << "ORDER - " << seq++;
    return os.str();
}

/**
 * @brief Creates a new Order
 * @param customerId The ID of the customer placing the order
 * @param lines The line items in the order
 * @returns The unique ID of the created order
 */
std::string SalesService::createOrder(std::string customerId, std::vector<OrderLine>& lines) 
{
    Order o;

    o.orderId = nextOrderId();
    o.customerId = customerId;
    o.lines = lines;
    o.staffId = std::nullopt;
    o.status = OrderStatus::New;
    o.type = OrderType::Created; 

    orders.emplace(o.orderId, o);
    notify(o);
    return o.orderId;
}

/**
 * @brief Assigns an Order to a staff member
 * @param orderId The unique ID of the order
 * @param staffId The ID of the staff member to assign
 * @returns true if the assignment was successful, false otherwise
 */
bool SalesService::assign(std::string orderId, std::string staffId) 
{
    auto it = orders.find(orderId);
    if (it == orders.end()) return false;

    Order& o = it->second;
    o.staffId = staffId;

    if (o.status == OrderStatus::New) 
    {
      o.status = OrderStatus::Assigned;
    }
    
    o.type = OrderType::Assigned;
    return true;
}

/**
 * @brief Updates the status of an Order
 * @param orderId The unique ID of the order
 * @param newStatus The new status to set for the order
 * @returns true if the status update was successful, false otherwise
 */
bool SalesService::updateStatus(std::string orderId, OrderStatus newStatus) 
{
    auto it = orders.find(orderId);
    if (it == orders.end()) return false;

    Order& o = it->second;
    o.status = newStatus;
    
    if (newStatus == OrderStatus::Completed) 
    {
        o.type = OrderType::Completed;
    } 
    else if (newStatus == OrderStatus::Cancelled) 
    {
        o.type = OrderType::Cancelled;
    }

    return true;
}

/**
 * @brief Gets an Order by its ID
 * @param orderId The unique ID of the order
 * @return optional<Order> if Order is found, null otherwise
 */
std::optional<Order> SalesService::get(std::string orderId) 
{
    auto it = orders.find(orderId);

    if (it == orders.end()) return std::nullopt;
    return it->second;
}

/**
 * @brief Gets the Orders of a staff member
 * @param staffId The ID of the staff member
 * @returns A vector of Orders assigned to the specified staff member
 */
std::vector<Order> SalesService::listByStaff(std::string staffId)  
{
    std::vector<Order> out;

    for (const auto& [id, o] : orders) 
    {
        if (o.staffId && *o.staffId == staffId) 
	    {
            out.push_back(o);
        } 
    }
    return out;
}

/**
 * @brief Gets the Orders of a customer
 * @param customerId The ID of the customer
 * @returns A vector of Orders associated with the specified customer
 */
std::vector<events::Order> SalesService::getOrdersByCustomer(std::string customerId)
{
    std::vector<events::Order> result;
    for (auto& [id, order] : orders)
    {
        if (order.customerId == customerId) result.push_back(order);
    }
    return result;
}

/**
 * @brief Gets the Orders assigned to a staff member
 * @param staffId The ID of the staff member
 * @returns A vector of Orders assigned to the specified staff member
 */
std::vector<events::Order> SalesService::getOrdersByStaff(std::string staffId)
{
    std::vector<events::Order> result;
    for (auto& [id, order] : orders)
    {
        if (order.staffId && *(order.staffId) == staffId) result.push_back(order);
    }
    return result;
}

/**
 * @brief Processes checkout for an order
 * @param customerId The ID of the customer
 * @param lines The line items in the order
 * @param amountPaid The amount paid by the customer
 * @details Calculates total cost, verifies payment, creates order, and generates receipt.
 * @returns A Receipt containing details of the transaction
 */
Receipt SalesService::checkout(std::string customerId, std::vector<events::OrderLine>& lines, double amountPaid)
{
    Receipt receipt;
    receipt.success = false;
    receipt.orderId = "";
    receipt.amountPaid = amountPaid;
    
    if (lines.empty())
    {
        receipt.message = "Cart is empty";
        receipt.totalCost = 0.0;
        receipt.change = 0.0;
        return receipt;
    }
    
    double total = 0.0;
    for (const auto& line : lines) 
    {
        total += line.finalCost;
    }
    receipt.totalCost = total;
    
    if (amountPaid < total) 
    {
        receipt.message = "Insufficient payment. Required: R" + std::to_string(total);
        receipt.change = 0.0;
        return receipt;
    }
    
    std::string orderId = createOrder(customerId, lines);
    if (orderId.empty()) 
    {
        receipt.message = "Failed to create order";
        receipt.change = 0.0;
        return receipt;
    }
    
    receipt.change = amountPaid - total;
    receipt.orderId = orderId;
    receipt.success = true;
    receipt.message = "Payment successful";
    receipts[orderId] = receipt;
    
      return receipt;
}

/**
 * @brief Retrieves a receipt by order ID
 * @param orderId The unique ID of the order
 * @returns An optional Receipt if found, empty otherwise
 */
std::optional<Receipt> SalesService::getReceipt(std::string orderId)
{
    auto it = receipts.find(orderId);
    if (it == receipts.end()) return std::nullopt;
    return it->second;
}

/**
 * @brief Retrieves all receipts for a customer
 * @param customerId The ID of the customer
 * @returns A vector of Receipts associated with the specified customer
 */
std::vector<Receipt> SalesService::getCustomerReceipts(std::string customerId)
{
    std::vector<Receipt> result;
    for (const auto& [orderId, receipt] : receipts) 
    {
        auto orderOpt = get(orderId);
        if (orderOpt && orderOpt->customerId == customerId)
        {
            result.push_back(receipt);
        }
    }
    return result;
}