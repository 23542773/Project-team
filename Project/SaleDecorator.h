#ifndef SALEDECORATOR_H
#define SALEDECORATOR_H
#include "SaleItem.h"

class SaleDecorator : public SaleItem 
{
public:

    explicit SaleDecorator(std::unique_ptr<SaleItem> inner): innerComp(std::move(inner)) {}

protected:

    SaleItem& getInnerComp() { return *innerComp; }

private:

    std::unique_ptr<SaleItem> innerComp;
};

#endif