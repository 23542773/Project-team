/**
* @file Events.h
* @brief Event data structures for Observer
* @author Damian Moustakis (Doxygen comments)
* @date 2025-11-01
* 
* @details
* The system supports three main event categories:
* - Plant Events: Lifecycle changes in individual plants (wilted, matured, died)
* - Stock Events: Inventory level changes (reserved, released, sold, low)
* - Order Events: Order lifecycle changes (created, assigned, completed, cancelled)
*/
#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include <vector>
#include <optional>

/**
* @namespace events
* @brief Contains all event types and data structures for the Observer pattern 
*/
namespace events 
{
    /**
     * @enum OrderType
     * @brief Represents the type of order event that occurred
    */
    enum class OrderType { Created, Assigned, Completed, Cancelled };
    /**
     * @enum StockType
     * @brief Represents a type of stock event that occured
     */
    enum class StockType { Reserved, Released, Sold, Low };
    /**
     * @enum PlantType
     * @brief Represents a type of plant lifecycle event
     */
    enum class PlantType { Wilted, Matured, Died};
    /**
     * @enum OrderStatus
     * @brief Current status of an order in the system
     */
    enum class OrderStatus { New, Assigned, InProgress, Completed, Cancelled };

    /**
     * @struct OrderLine
     * @brief Represents a single line item in an order
     */
    struct OrderLine
    {
        std::string plantId;
        std::string speciesSku;
        std::string description;
        double finalCost = 0.0;
    };

    /**
     * @struct Order
     * @brief Contains all info related to Order events
     */
    struct Order 
    { 
        std::string orderId; 
        std::string customerId;
        std::vector<OrderLine> lines;
        std::optional<std::string> staffId;
        OrderType type; 
        OrderStatus status = OrderStatus::New;   
    };

    /**
     * @struct Stock
     * @brief Contains all info related to Stock events
     */
    struct Stock 
    { 
        std::string key; 
        StockType type; 
    }; 

    /**
     * @struct Plant
     * @brief Plant lifecycle info for Plant events
     */
    struct Plant 
    { 
        std::string plantId; 
        std::string sku;
        PlantType type; 
    };
}

#endif // EVENTS_H