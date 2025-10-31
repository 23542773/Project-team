#ifndef SALEITEM_H
#define SALEITEM_H
#include <memory>
#include <string>
#include "Plant.h"

class SaleItem 
{
public:

    virtual ~SaleItem() = default;
    virtual double cost() = 0;
    virtual std::string description() = 0;
};
#endif