#ifndef GIFTWRAP_H
#define GIFTWRAP_H
#include "SaleDecorator.h"

class GiftWrap : public SaleDecorator 
{
public:

    explicit GiftWrap(std::unique_ptr<SaleItem> inner);
    double cost() override;
    std::string description() override;
};
#endif