#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>


struct OrderItem 
{
    std::string id;
    double price;
    std::string type;
    int quantity;
    
    /**
     * @brief Default constructor
     */
    OrderItem() : price(0.0), quantity(1) {}
    
    /**
     * @brief Virtual destructor
     */
    virtual ~OrderItem() = default;
};

#endif // ORDERITEM_H