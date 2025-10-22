#ifndef NURSERYFACADE_H
#define NURSERYFACADE_H

#include <string>
#include <vector>

class SpeciesCatalog;
class InventoryService;
class SalesService;

//abstact base version of the facade
class NurseryFacade
{
    protected:
        SpeciesCatalog* catalog;
        InventoryService* inv;
        SalesService* sales;
        NurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales);

    public:
        virtual ~NurseryFacade() = default;
        virtual bool isValid() const = 0;
        //not sure if we can use this might help for validation later on
        //bool SharedSubsystemsValid() const;

    private:
        //thiking we need to attach lifecycles to each facade
        //up for deliberation
        //NurseryFacade(const NurseryFacade&) = delete;
        //NurseryFacade& operator=(const NurseryFacade&) = delete;
        //NurseryFacade(NurseryFacade&&) = delete;
        //NurseryFacade& operator=(NurseryFacade&&) = delete; 

};
#endif