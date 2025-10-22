#ifndef STAFFNURSERYFACADE_H
#define STAFFNURSERYFACADE_H

#include "NurseryFacade.h"
#include <string>
#include <vector>

class StaffNurseryFacade : public NurseryFacade 
{

    public:
        StaffNurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales);
        ~StaffNurseryFacade();
        void restock(const std::string& sku, int qty);
        std::vector<std::string> getReadyForSale();
        bool isAvailableForPurchase(const std::string& sku);
        std::string validateStock(const std::string& sku, int requiredQty);
        std::string getInventorySummary();

        //optional alerts we can add in
        //std::vector<std::string> getLowStockAlert();
        //std::vector<std::string> getOutOfStockItems();
        bool isValid() const override;

};

#endif