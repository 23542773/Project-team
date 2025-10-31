/**
 * @file SaleDecorator.h
 * @brief Declares the SaleDecorator abstract class for decorating SaleItem objects.
 * 
 * SaleDecorator provides a base class for concrete decorators, allowing dynamic
 * modification of cost and description of SaleItem objects using the Decorator pattern.
 * 
 * @date 2025-10-31
 */

#ifndef SALEDECORATOR_H
#define SALEDECORATOR_H

#include "SaleItem.h"

/**
 * @class SaleDecorator
 * @brief Abstract decorator for SaleItem objects.
 * 
 * Wraps a SaleItem and allows derived classes to modify its behavior (e.g., cost, description).
 */
class SaleDecorator : public SaleItem 
{
public:

    /**
     * @brief Constructs a SaleDecorator wrapping an existing SaleItem.
     * @param inner Unique pointer to the SaleItem to decorate.
     */
    explicit SaleDecorator(std::unique_ptr<SaleItem> inner): innerComp(std::move(inner)) {}

protected:

    /**
     * @brief Provides access to the wrapped SaleItem.
     * @return Reference to the inner SaleItem.
     */
    SaleItem& getInnerComp() { return *innerComp; }

private:

    /// Unique pointer to the wrapped SaleItem.
    std::unique_ptr<SaleItem> innerComp;
};

#endif
