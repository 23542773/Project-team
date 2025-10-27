#ifndef NURSERYFACADE_H
#define NURSERYFACADE_H

#include <string>
#include <vector>

// Forward declarations - will be replaced with real classes when team finishes
class SpeciesCatalog;
class InventoryService;
class SalesService;

/**
 * @file NurseryFacade.h
 * @brief Abstract base facade for Plant Nursery Simulator
 * @author Damian Moustakis - COS 214 Project
 * @date 2025-10-27
 * 
 * TEMPORARY IMPLEMENTATION:
 * Currently uses dummy subsystem types. When real pattern implementations
 * are ready, simply swap the dummy includes for real class includes.
 */

// Abstract base version of the facade
class NurseryFacade
{
    protected:
        SpeciesCatalog* catalog;
        InventoryService* inv;
        SalesService* sales;
        
        /**
         * @brief Protected constructor - only derived classes can create instances
         * @param catalog Pointer to SpeciesCatalog
         * @param inv Pointer to InventoryService
         * @param sales Pointer to SalesService
         */
        NurseryFacade(SpeciesCatalog* catalog, InventoryService* inv, SalesService* sales);

    public:
        /**
         * @brief Virtual destructor for proper polymorphic cleanup
         */
        virtual ~NurseryFacade() = default;
        
        /**
         * @brief Validate facade is properly configured
         * @return true if all subsystems are valid
         */
        virtual bool isValid() const = 0;
        
        /**
         * @brief Check if shared subsystems are valid
         * @return true if catalog, inv, and sales are all non-null
         */
        bool areSharedSubsystemsValid() const;

    private:
        // Prevent copying and moving
        NurseryFacade(const NurseryFacade&) = delete;
        NurseryFacade& operator=(const NurseryFacade&) = delete;
        NurseryFacade(NurseryFacade&&) = delete;
        NurseryFacade& operator=(NurseryFacade&&) = delete; 
};

#endif // NURSERYFACADE_H