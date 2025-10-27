#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H

#include <string>
#include <vector>

class InventoryService 
{
    public:
        /**
         * @brief Virtual destructor
         */
        virtual ~InventoryService() = default;
        
        /**
         * @brief Check available stock for a SKU
         * @param sku SKU identifier
         * @return Quantity available (0 if not found)
         */
        virtual int available(const std::string& sku) const = 0;
        
        /**
         * @brief Restock (add) inventory
         * @param sku SKU to restock
         * @param qty Quantity to add
         */
        virtual void restock(const std::string& sku, int qty) = 0;
        
        /**
         * @brief Consume (remove) from inventory
         * @param sku SKU to consume
         * @param qty Quantity to consume
         * @return true if successful
         */
        virtual bool consume(const std::string& sku, int qty) = 0;
        
        /**
         * @brief Get all SKUs
         * @return Vector of all SKU strings
         */
        virtual std::vector<std::string> getAllSKUs() const = 0;
};

#endif // INVENTORYSERVICE_H