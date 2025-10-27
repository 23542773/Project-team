#ifndef DUMMY_ORDERITEM_H
#define DUMMY_ORDERITEM_H

#include <string>
#include "OrderItem.h"

/**
 * @file dummy/DummyOrderItem.h
 * @brief Standalone dummy OrderItem for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone
 * This is NOT a stub - it's a complete simple data structure
 */
struct DummyOrderItem : public OrderItem {
    std::string id;
    double price;
    std::string type;
    int quantity;

    /**
     * @brief Create dummy order item
     * 
     * @param id Item SKU
     * @param price Price in Rand
     * @param type Item type (default "plant")
     * @param qty Quantity (default 1)
     */
    DummyOrderItem(const std::string& id = "",
                   double price = 0.0,
                   const std::string& type = "plant",
                   int qty = 1)
        : id(id), price(price), type(type), quantity(qty) {}
};

#endif // DUMMY_ORDERITEM_H