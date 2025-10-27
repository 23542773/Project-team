#ifndef STAFFNURSERYFACADE_H
#define STAFFNURSERYFACADE_H

#include "NurseryFacade.h"
#include <string>
#include <vector>

/**
 * @file StaffNurseryFacade.h
 * @brief Staff-facing facade for nursery management operations
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 */

class StaffNurseryFacade : public NurseryFacade
{
    public:
        /**
         * @brief Constructor
         * @param catalog Pointer to SpeciesCatalog
         * @param inv Pointer to InventoryService
         * @param sales Pointer to SalesService
         */
        StaffNurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales);

        /**
         * @brief Destructor
         */
        ~StaffNurseryFacade();
        
        /**
         * @brief Restock inventory with new plants from supplier
         * @param sku SKU identifier to restock
         * @param qty Quantity to add to inventory
         */
        void restock(const std::string& sku, int qty);
        
        /**
         * @brief Get list of plants ready for sale (in MATURE state)
         * @return Vector of SKUs for plants ready to sell
         */
        std::vector<std::string> getReadyForSale();
        
        /**
         * @brief Check if specific plant is available for purchase
         * @param sku SKU to check
         * @return true if in stock AND in sellable state
         */
        bool isAvailableForPurchase(const std::string& sku);
        
        /**
         * @brief Validate stock availability and return detailed status
         * @param sku SKU to validate
         * @param requiredQty Quantity needed
         * @return Status string (AVAILABLE, PARTIAL, UNAVAILABLE, INVALID_SKU)
         */
        std::string validateStock(const std::string& sku, int requiredQty);
        
        /**
         * @brief Get comprehensive inventory summary for staff dashboard
         * @return Formatted summary string
         */
        std::string getInventorySummary();
        
        /**
         * @brief Validate facade is properly configured
         * @return true if all subsystems are valid
         */
        bool isValid() const override;
};

#endif // STAFFNURSERYFACADE_H