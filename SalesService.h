#ifndef SALESSERVICE_H
#define SALESSERVICE_H

#include <string>
#include <vector>

// Forward declaration
struct OrderItem;

class SalesService 
{
    public:
        /**
         * @brief Virtual destructor
         */
        virtual ~SalesService() = default;
        
        /**
         * @brief Check if customer exists
         * @param custId Customer ID
         * @return true if customer exists
         */
        virtual bool customerExists(const std::string& custId) const = 0;
        
        /**
         * @brief Create a new order
         * @param custId Customer ID
         * @param items Vector of OrderItems
         * @return Order ID
         */
        virtual std::string createOrder(const std::string& custId, const std::vector<OrderItem*>& items) = 0;
};

#endif // SALESSERVICE_H