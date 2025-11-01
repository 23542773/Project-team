#include "SalesService.h"
#include <sstream>
#include <iomanip>
using events::Order;
using events::OrderLine;
using events::OrderType;
using events::OrderStatus;

std::string SalesService::nextOrderId() 
{
    std::ostringstream os;
    os << "ORDER - " << seq++;
    return os.str();
}

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

std::optional<Order> SalesService::get(std::string orderId) 
{
    auto it = orders.find(orderId);

    if (it == orders.end()) return std::nullopt;
    return it->second;
}

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

std::vector<events::Order> SalesService::getOrdersByCustomer(std::string customerId)
{
    std::vector<events::Order> result;
    for (auto& [id, order] : orders)
    {
        if (order.customerId == customerId) result.push_back(order);
    }
    return result;
}

std::vector<events::Order> SalesService::getOrdersByStaff(std::string staffId)
{
    std::vector<events::Order> result;
    for (auto& [id, order] : orders)
    {
        if (order.staffId && *(order.staffId) == staffId) result.push_back(order);
    }
    return result;
}

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

std::optional<Receipt> SalesService::getReceipt(std::string orderId)
{
    auto it = receipts.find(orderId);
    if (it == receipts.end()) return std::nullopt;
    return it->second;
}

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