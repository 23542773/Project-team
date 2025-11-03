#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include <vector>
#include <optional>

namespace events 
{
    /// \brief Enum classes representing various "states" pertaining to the necessary Order/Stock/Plant events
    enum class OrderType { Created, Assigned, Completed, Cancelled };
    enum class StockType { Reserved, Released, Sold, Low, Added };
    enum class PlantType { Wilted, Matured, Died};
    enum class OrderStatus { New, Assigned, InProgress, Completed, Cancelled };

    /// \brief Represents a single line in an Order
    struct OrderLine
    {
        std::string plantId;
        std::string speciesSku;
        std::string description;
        double finalCost = 0.0;
    };

    /// \brief Order Struct contains all info related to an Order and is used to trigger Order Events within the system
    struct Order 
    { 
        std::string orderId; 
        std::string customerId;
        std::vector<OrderLine> lines;
        std::optional<std::string> staffId;
        OrderType type; 
        OrderStatus status = OrderStatus::New;   
    };

    /// \brief Stock Struct contains all info related to Stock and is used to trigger Stock Events within the system
    struct Stock 
    { 
        std::string key; 
        StockType type; 
    }; 

    /// \brief Plant Struct contains all info related to a Plant and is used to trigger Plant Events within the system
    /// \note Plant here represent a Plant Event and not a Plant object
    struct Plant 
    { 
        std::string plantId; 
        std::string sku;
        PlantType type; 
    };
}

#endif