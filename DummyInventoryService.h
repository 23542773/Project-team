#ifndef DUMMY_INVENTORYSERVICE_H
#define DUMMY_INVENTORYSERVICE_H

#include "InventoryService.h"
#include <map>
#include <string>
#include <vector>

/**
 * @file dummy/DummyInventoryService.h
 * @brief Standalone dummy InventoryService for testing
 * @author damian Moustakis - COS 214 Project
 * @date 2025-10-26
 * 
 * TESTING PURPOSE ONLY - Completely standalone, no real class dependency
 * Later: Replace with real InventoryService implementation
 */

// Forward declaration
class DummyPlant;

/**
 * @class DummyInventoryService
 * @brief Standalone dummy inventory service - NO INHERITANCE
 * 
 * When real InventoryService is ready, change this to inherit from InventoryService.
 */
class DummyInventoryService:public InventoryService {
private:
    std::map<std::string, int> stock;
    std::map<std::string, DummyPlant*> plants;

public:
    /**
     * @brief Constructor - automatically populates with dummy stock
     * 
     * Initializes inventory with:
     * - SUCC-001: 15 units
     * - CACT-001: 8 units
     * - ORCH-001: 3 units
     * - HERB-023: 20 units
     * - FERN-005: 5 units
     */
    DummyInventoryService();

    ~DummyInventoryService();

    /**
     * @brief Add stock for a SKU
     * @param sku SKU identifier
     * @param qty Quantity to add
     */
    void add(const std::string& sku, int qty);

    /**
     * @brief Remove stock for a SKU
     * @param sku SKU identifier
     * @param qty Quantity to remove
     * @return true if successful, false if insufficient stock
     */
    bool remove(const std::string& sku, int qty);

    /**
     * @brief Check available stock for a SKU
     * @param sku SKU identifier
     * @return Quantity available (0 if not found)
     */
    int available(const std::string& sku) const;

    /**
     * @brief Restock (add) inventory
     * @param sku SKU to restock
     * @param qty Quantity to add
     */
    void restock(const std::string& sku, int qty);

    /**
     * @brief Consume (remove) from inventory
     * @param sku SKU to consume
     * @param qty Quantity to consume
     * @return true if successful
     */
    bool consume(const std::string& sku, int qty);

    /**
     * @brief Store a plant in inventory
     * @param sku SKU identifier
     * @param plant Plant to store
     */
    void addPlant(const std::string& sku, DummyPlant* plant);

    /**
     * @brief Get plant from inventory
     * @param sku SKU identifier
     * @return Pointer to DummyPlant, or nullptr if not found
     */
    DummyPlant* getPlant(const std::string& sku) const;

    /**
     * @brief Get all plants
     * @return Vector of all plants
     */
    std::vector<DummyPlant*> getAllPlants() const;

    /**
     * @brief Get all SKUs
     * @return Vector of all SKU strings
     */
    std::vector<std::string> getAllSKUs() const;
};

#endif // DUMMY_INVENTORYSERVICE_H