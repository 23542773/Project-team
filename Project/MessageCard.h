#ifndef MESSAGECARD_H
#define MESSAGECARD_H
#include "SaleDecorator.h"
#include <string>

class MessageCard : public SaleDecorator 
{
public:

    explicit MessageCard(std::unique_ptr<SaleItem> inner, std::string msg);
    double cost() override;
    std::string description() override;

private:

    std::string msg;
};
#endif