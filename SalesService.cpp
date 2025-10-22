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

    notify(o);
    return true;
}

bool SalesService::updateStatus(std::string orderId, OrderStatus newStatus) 
{
    auto it = orders.find(orderId);
    if (it == orders.end()) return false;

    Order& o = it->second;
    o.status = newStatus;

    notify(o);
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
