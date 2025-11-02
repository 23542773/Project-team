/**
 * @file Events.h
 * @brief Defines the data structures and enumerations used to represent various events
 * (Order, Stock, Plant) that occur within the system.
 */

#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <vector>
#include <optional>

/**
 * @namespace events
 * @brief Contains all event-related enumerations and data structures (payloads).
 */
namespace events
{
    /**
     * @enum OrderType
     * @brief Represents the high-level action type related to an Order event.
     */
    enum class OrderType {
        /** @brief A new order has been created. */
        Created,
        /** @brief An order has been assigned to a staff member. */
        Assigned,
        /** @brief An order has been completed (fulfilled/shipped). */
        Completed,
        /** @brief An order has been cancelled. */
        Cancelled
    };

    /**
     * @enum StockType
     * @brief Represents the high-level action type related to a Stock event.
     */
    enum class StockType {
        /** @brief Stock quantity has been reserved for an order. */
        Reserved,
        /** @brief Reserved stock has been released (e.g., due to cancellation). */
        Released,
        /** @brief Stock has been permanently sold and removed from inventory. */
        Sold,
        /** @brief Stock quantity for a species is running low. */
        Low
    };

    /**
     * @enum PlantType
     * @brief Represents the high-level action type related to a Plant event.
     */
    enum class PlantType {
        /** @brief A plant has wilted or is in poor condition. */
        Wilted,
        /** @brief A plant has reached maturity. */
        Matured,
        /** @brief A plant has died and needs to be removed from the nursery. */
        Died
    };

    /**
     * @enum OrderStatus
     * @brief Represents the current processing state of an Order.
     */
    enum class OrderStatus {
        /** @brief Order just entered the system. */
        New,
        /** @brief Order is assigned to a staff member. */
        Assigned,
        /** @brief Order is being processed/picked. */
        InProgress,
        /** @brief Order has been fully processed. */
        Completed,
        /** @brief Order has been formally cancelled. */
        Cancelled
    };

    /**
     * @struct OrderLine
     * @brief Represents a single line item within a customer's order.
     */
    struct OrderLine
    {
        /** @brief The unique ID of the specific plant being ordered (if applicable). */
        std::string plantId;
        /** @brief The Stock Keeping Unit (SKU) for the species. */
        std::string speciesSku;
        /** @brief A short description of the line item. */
        std::string description;
        /** @brief The final cost for this specific line item. */
        double finalCost = 0.0;
    };

    /**
     * @struct Order
     * @brief Data structure containing all information about an order event.
     */
    struct Order
    {
        /** @brief The unique identifier for the order. */
        std::string orderId;
        /** @brief The unique identifier for the customer who placed the order. */
        std::string customerId;
        /** @brief A list of all line items included in the order. */
        std::vector<OrderLine> lines;
        /** @brief Optional ID of the staff member currently assigned to the order. */
        std::optional<std::string> staffId;
        /** @brief The type of order action/event being reported. */
        OrderType type;
        /** @brief The current status of the order. Defaults to New. */
        OrderStatus status = OrderStatus::New;
    };

    /**
     * @struct Stock
     * @brief Data structure containing information related to a stock event.
     */
    struct Stock
    {
        /** @brief The identifier for the stock item (e.g., SKU or unique stock ID). */
        std::string key;
        /** @brief The type of stock action/event being reported. */
        StockType type;
    };

    /**
     * @struct Plant
     * @brief Data structure containing information related to a specific plant event.
     * @note This struct represents the event payload, not a persistent Plant object.
     */
    struct Plant
    {
        /** @brief The unique ID of the individual plant. */
        std::string plantId;
        /** @brief The SKU of the plant's species. */
        std::string sku;
        /** @brief The type of plant status change/event being reported. */
        PlantType type;
    };
}

#endif